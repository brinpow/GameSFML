#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <random>

using namespace sf;

int signum(float);

Font load_font(std::string);

Text create_text(std::string, Font&, int, Color);

Color choose_random_color();

void play_music(Music& , std::string);