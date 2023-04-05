#include "Food.h"

Food::Food(float x, float y)
{
	shape.setPosition(x, y);
	shape.setSize(Vector2f(size, size));
	shape.setOrigin(Vector2f(size / 2, size / 2));
	if (!texture.loadFromFile("resources/images/strawberry.png"))
	{
		throw "Wrong path";
	}
	shape.setTexture(&texture);
}

void Food::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(shape, state);
}

RectangleShape Food::get_shape() const&
{
	return shape;
}

Vector2f Food::get_postion() const&
{
	return shape.getPosition();
}

void Food::set_position(float x, float y)
{
	shape.setPosition(x, y);
}

void Food::set_random_image()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 6);
    switch (dist6(rng))
    {
        case 1:
            if (!texture.loadFromFile("resources/images/banana.png"))
            {
                throw "Wrong path";
            }
            break;
        case 2:
            if (!texture.loadFromFile("resources/images/blueberries.png"))
            {
                throw "Wrong path";
            }
            break;
        case 3:
            if (!texture.loadFromFile("resources/images/carrots.png"))
            {
                throw "Wrong path";
            }
            break;
        case 4:
            if (!texture.loadFromFile("resources/images/lemon.png"))
            {
                throw "Wrong path";
            }
            break;
        case 5:
            if (!texture.loadFromFile("resources/images/pepper.png"))
            {
                throw "Wrong path";
            }
            break;
        default:
            if (!texture.loadFromFile("resources/images/strawberry.png"))
            {
                throw "Wrong path";
            }
            break;
    }
}