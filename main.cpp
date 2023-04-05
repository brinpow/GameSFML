#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Segment.h"
#include "config.h"
#include "Food.h"
#include <iostream>
#include <list>
#include <random>
#include <iterator>
#include "Game.h"
#include "utilities.h"
#include "button.h"

using namespace sf;

float segment_size = 50.0f;
int food_size = 35;

inline bool eat_check(const Segment& head, const Food& food)
{
    return head.get_shape().getGlobalBounds().intersects(food.get_shape().getGlobalBounds());
}

bool hit_check(const std::list<Segment>& snake_body, size_t size)
{
    bool check = false;
    if (size > 3)
    {
        Segment head = snake_body.front();
        auto it = snake_body.begin();
        std::advance(it, 3);
        for (; it != snake_body.end(); it++)
        {
            if (head.hit_check(*it))
            {
                check=true;
                break;
            }
        }
    }

    return check;
}

void add_new_segment(std::list<Segment>& snake_body)
{
    Segment tail = snake_body.back();
    Color color = choose_random_color();
    Segment _new(tail.get_postion().x - signum(tail.get_velocity().x)*segment_size, tail.get_postion().y - signum(tail.get_velocity().y)*segment_size, color);
    _new.set_velocity(tail.get_velocity());
    _new.set_direct_changes(tail);
    snake_body.push_back(_new);
}

void new_Food(Food& food, std::list<Segment>& snake_body)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> cord_x(food_size+1, LENGTH - food_size);
    std::uniform_int_distribution<std::mt19937::result_type> cord_y(food_size+1, HEIGHT - food_size);
    float x;
    float y;
    Food test(0, 0);
    bool check = false;
    while (!check)
    {
        x = static_cast<float>(cord_x(rng));
        y = static_cast<float>(cord_y(rng));
        test.set_position(x, y);
        check = true;
        for (auto it = snake_body.begin(); it != snake_body.end(); it++)
        {
            if (eat_check(*it, test))
            {
                check = false;
                break;
            }
        }
    }
    food.set_position(x, y);
    food.set_random_image();
}

int main()
{
    Game game(2);
    RenderWindow& window = game.window;
    Event event;

    bool game_over = false;
    bool pause = false;
    Segment head(1000, 400,Color::Red);
    head.set_velocity(Vector2f(-3.0f, 0));

    Food food(300, 400);

    std::list<Segment> snake_body;
    snake_body.push_back(head);

    int score = 0;
    int timer = 16;
    int first = 0;
    Music music;
    Font arial = load_font("resources/fonts/arial.ttf");
    Button ext("Exit", Vector2f(50, 40), 20, Color::Green, Color::Black,arial);
    Button again("Play again", Vector2f(100, 40), 20, Color::Green, Color::Black, arial);

    ext.set_position(Vector2f(LENGTH/2-100, HEIGHT/2+50));
    again.set_position(Vector2f(LENGTH/2 -40, HEIGHT/2 + 50));

    while (window.isOpen())
    {
        window.clear(Color::Black);
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case Event::Closed:
                    window.close();
                    break;
                case Event::MouseMoved:
                    Button::button_hover(ext, window, Color::White);
                    Button::button_hover(again, window, Color::White);
                    break;
                case Event::MouseButtonPressed:
                    if (ext.is_hovered(window))
                    {
                        window.close();
                    }
                    if (again.is_hovered(window))
                    {
                        score = 0;
                        timer = 16;
                        first = 0;
                        game_over = false;
                        snake_body.clear();
                        snake_body.push_back(head);
                        food.set_position(300, 400);
                        auto it = game.text_list.begin();
                        std::advance(it, 1);
                        it->second = false;
                        game.update_score(score);
                    }
                    break;
                case Event::KeyPressed:
                    if (event.key.code == Keyboard::P and !game_over)
                    {
                        pause = !pause;
                        game.text_list.back().second = !game.text_list.back().second;
                    }
            }
        }

        size_t size = snake_body.size();
        game_over = game_over or hit_check(snake_body, size) or snake_body.begin()->check_bounds();

        if(game_over and first<2)
        {
            first++;
        }

        if (eat_check(snake_body.front(), food))
        {
            play_music(music, "resources/music/eat.ogg");
            add_new_segment(snake_body);
            new_Food(food, snake_body);
            score++;
            game.update_score(score);
        }

        if (!game_over and !pause)
        {
            if (!timer)
            {
                snake_body.front().update_head(snake_body);
                auto it = --snake_body.end();
                for (it; it != snake_body.begin(); it--)
                {
                    it->update();
                }
                timer = std::max(16 - score,0);
            }
            else
            {
                timer--;
            }
        }
        else if(game_over)
        {
            if(first==1)
            {
                play_music(music, "resources/music/gameOver.ogg");
            }

            auto it = game.text_list.begin();
            std::advance(it, 1);
            it->second = true;
        }

        for (auto it = snake_body.begin(); it != snake_body.end(); it++)
        {
            window.draw(*it);
        }
        window.draw(food);
        for (auto it = game.text_list.begin(); it != game.text_list.end(); it++)
        {
            if(it->second)
            {
                window.draw(it->first);
            }
        }
        if (game_over)
        {
            ext.drawTo(window);
            again.drawTo(window);
        }
        window.display();
    }

    return 0;
}