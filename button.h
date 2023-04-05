#pragma once

#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

class Button {
public:
	Button();

	Button(std::string, Vector2f, int, Color, Color, Font&);

	void set_text(std::string);

	void set_size(Vector2f);

	void set_char_size(int);

	void set_background_color(Color);

	void set_text_color(Color);

	void set_position(Vector2f);

	void drawTo(RenderWindow&);

	bool is_hovered(RenderWindow&);

	static void button_hover(Button&,RenderWindow&,Color);

	static void button_clicked();
private:
	RectangleShape button;
	Text text;

	float button_width;
	float button_height;

	Color bg_color;
};

