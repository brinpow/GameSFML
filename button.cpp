#include "button.h"
#include <iostream>

Button::Button() {

}

Button::Button(std::string text, Vector2f buttonSize, int char_size, Color bg_color, Color text_color, Font& font) {
	button.setSize(buttonSize);
	button.setFillColor(bg_color);

	button_width = buttonSize.x;
	button_height = buttonSize.y;

	this->text.setFont(font);
	this->text.setString(text);
	this->text.setCharacterSize(char_size);
	this->text.setFillColor(text_color);

	this->bg_color = bg_color;
}

void Button::set_text(std::string text) {
	this->text.setString(text);
}

void Button::set_size(sf::Vector2f size) {
	button.setSize(size);
}

void Button::set_char_size(int size) {
	text.setCharacterSize(size);
}

void Button::set_background_color(Color color) {
	button.setFillColor(color);
}

void Button::set_text_color(Color color) {
	text.setFillColor(color);
}

void Button::set_position(Vector2f position) {
	button.setPosition(position);

	float x_pos = position.x + button_width/2 - text.getLocalBounds().width/2;
	float y_pos = position.y + button_height/2 - static_cast<float>(text.getCharacterSize()/2);
	text.setPosition(x_pos, y_pos);
}

void Button::drawTo(sf::RenderWindow& window) {
	window.draw(button);
	window.draw(text);
}

bool Button::is_hovered(RenderWindow& window) {
	Vector2i mouse_coords({ Mouse::getPosition(window).x, Mouse::getPosition(window).y });

	Vector2f real_coords = window.mapPixelToCoords(mouse_coords);

	float mouseX = real_coords.x;
	float mouseY = real_coords.y;

	float btn_posX = button.getPosition().x;
	float btn_posY = button.getPosition().y;

	float btnxPosWidth = button.getPosition().x + button.getGlobalBounds().width;
	float btnyPosHeight = button.getPosition().y + button.getGlobalBounds().height;

	if (mouseX < btnxPosWidth + 20 and mouseX > btn_posX - 20 and mouseY < btnyPosHeight + 20 and mouseY > btn_posY - 20) {
		return true;
	}
	return false;
}

void Button::button_hover(Button& button, RenderWindow& window, Color color)
{
	if (button.is_hovered(window))
	{
		button.set_background_color(color);
	}
	else
	{
		button.set_background_color(button.bg_color);
	}
}