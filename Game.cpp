#include "Game.h"
#include <sstream>

Game::Game(int length):window(VideoMode(LENGTH, HEIGHT), "Snake")
{
	window.setFramerateLimit(FRAME_RATE);

    arial = load_font("resources/fonts/arial.ttf");

    Text text_score = create_text("Score 0", arial, 50, Color::Green);
    text_score.setPosition(6, 3);
    Text text_game_over = create_text("GAME OVER", arial, 100, Color::Red);
    text_game_over.setPosition(LENGTH / 2 - text_game_over.getLocalBounds().width / 2, HEIGHT / 2 - text_game_over.getLocalBounds().height);
    Text text_pause = create_text("PAUSE", arial, 100, Color::Green);
    text_pause.setPosition(LENGTH / 2 - text_pause.getLocalBounds().width / 2, HEIGHT / 2 - text_pause.getLocalBounds().height);
    text_list.push_back(std::make_pair(text_score,true));
    text_list.push_back(std::make_pair(text_game_over,false));
    text_list.push_back(std::make_pair(text_pause, false));
}

void Game::update_score(int score)
{
    std::ostringstream ss;
    ss << score;
    text_list.front().first.setString("Score " + ss.str());
}
