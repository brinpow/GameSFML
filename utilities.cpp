#include "utilities.h"

int signum(float x)
{
    return (x > 0) - (x < 0);
}

Font load_font(std::string path)
{
    Font font;
    if (!font.loadFromFile(path))
    {
        exit(EXIT_FAILURE);
    }
    return font;
}

Text create_text(std::string message, Font& font, int size, Color color)
{
    Text text(message,font, size);
    text.setFillColor(color);
    return text;
}

Color choose_random_color()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 6);
    Color color;
    switch (dist6(rng))
    {
        case 1:
            color = Color::White;
            break;
        case 2:
            color = Color::Cyan;
            break;
        case 3:
            color = Color::Green;
            break;
        case 4:
            color = Color::Blue;
            break;
        case 5:
            color = Color::Yellow;
            break;
        case 6:
            color = Color::Magenta;
            break;
    }
    return color;
}

void play_music(Music& music, std::string path)
{
    if (!music.openFromFile(path))
    {
        throw "Wrong path!";
    }
    music.play();
}