#pragma once
#include <SFML/Graphics.hpp>
#include "utilities.h"

using namespace sf;

class Food:public Drawable
{
	float size = 35.f;
	RectangleShape shape;
	Texture texture;
public:
	Food(float x, float y);

	void draw(RenderTarget& target, RenderStates state) const override;

	RectangleShape get_shape() const&;

	Vector2f get_postion() const&;

	void set_position(float,float);

	void set_random_image();
};

