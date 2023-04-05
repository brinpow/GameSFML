#pragma once
#include <SFML/Graphics.hpp>
#include "config.h"
#include "utilities.h"
#include <list>
#include <vector>

using namespace sf;

class Game
{
	Font arial;
public:
	std::list<std::pair<Text,bool>> text_list;
	RenderWindow window;

	Game(int);

	void update_score(int);
};

