#include "Segment.h"
#include <iostream>
#include "utilities.h"

float Segment::size = 50.f;
float Segment::velocity_x = 3.0f;
float Segment::velocity_y = 3.0f;

Segment::Segment(float x, float y,const Color& color,float size)
{
	shape.setPosition(x, y);
	shape.setFillColor(color);
	shape.setSize(Vector2f(size, size));
	shape.setOrigin(Vector2f(size / 2, size / 2));
	velocity = Vector2f(0.f, 0.f);
	this->size = size;
}

void Segment::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(shape, state);
}

bool Segment::check_bounds()
{
	if (shape.getPosition().x < size/2 and velocity.x<0)
	{
		return true;
	}
	if (LENGTH - shape.getPosition().x < size/2 and velocity.x>0)
	{
		return true;
	}
	if (shape.getPosition().y < size/2 and velocity.y < 0)
	{
		return true;
	}
	if (HEIGHT - shape.getPosition().y < size/2 and velocity.y>0)
	{
		return true;
	}
	return false;
}

void Segment::update_head(std::list<Segment>& snake_body)
{
	bool horizontally = Keyboard::isKeyPressed(Keyboard::Key::Left) or Keyboard::isKeyPressed(Keyboard::Key::Right);
	bool vertically = Keyboard::isKeyPressed(Keyboard::Key::Up) or Keyboard::isKeyPressed(Keyboard::Key::Down);
	bool change = true;
	velocity.x = signum(velocity.x) * Segment::velocity_x;
	velocity.y = signum(velocity.y) * Segment::velocity_y;
	if (horizontally and vertically)
	{
		int changes = 0;
		if (Keyboard::isKeyPressed(Keyboard::Key::Left) and velocity.x!= -velocity_x)
		{
			velocity.x = -velocity_x;
			changes++;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Key::Right) and velocity.x != velocity_x)
		{
			velocity.x = velocity_x;
			changes++;
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::Up) and velocity.y != -velocity_y)
		{
			velocity.y = -velocity_y;
			changes++;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Key::Down) and velocity.y != velocity_y)
		{
			velocity.y = velocity_y;
			changes++;
		}
		if (!changes)
		{
			change = false;
		}

	}
	else if(vertically)
	{
		if (Keyboard::isKeyPressed(Keyboard::Key::Up) and velocity.y != -velocity_y)
		{
			velocity.y = -velocity_y;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Key::Down) and velocity.y != velocity_y)
		{
			velocity.y = velocity_y;
		}
		else if(velocity.x==0)
		{
			change = false;
		}
		velocity.x = 0;
	}
	else if (horizontally)
	{
		if (Keyboard::isKeyPressed(Keyboard::Key::Left) and velocity.x != -velocity_x)
		{
			velocity.x = -velocity_x;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Key::Right) and velocity.x != velocity_x)
		{
			velocity.x = velocity_x;
		}
		else if(velocity.y==0)
		{
			change = false;
		}
		velocity.y = 0;
	}
	else
	{
		change = false;
	}
	if (change)
	{
		for (auto it = ++snake_body.begin(); it != snake_body.end(); it++)
		{
			it->direct_changes.push_front(std::make_pair(shape.getPosition(), velocity));
		}
	}
	shape.move(velocity);
}

void Segment::update()
{
	if (direct_changes.size()>0)
	{
		std::pair<Vector2f, Vector2f> pair = *(--direct_changes.end());
		float pos_x = signum(velocity.x) * (shape.getPosition().x - pair.first.x);
		float pos_y = signum(velocity.y) * (shape.getPosition().y - pair.first.y);
		if (pos_x <= velocity_x and pos_x>=0 and pos_y <= velocity_y and pos_y>=0)
		{
			velocity = pair.second;
			shape.setPosition(pair.first);
			direct_changes.pop_back();
		}
	}
	velocity.x = signum(velocity.x) * Segment::velocity_x;
	velocity.y = signum(velocity.y) * Segment::velocity_y;
	shape.move(velocity);
}

Vector2f Segment::get_postion() const &
{
	return shape.getPosition();
}

void Segment::set_velocity(const Vector2f& velocity)
{
	this->velocity = velocity;
}

Vector2f Segment::get_velocity() const
{
	return velocity;
}

RectangleShape Segment::get_shape() const&
{
	return shape;
}

void Segment::set_direct_changes(const Segment& tail)
{
	for (auto it = tail.direct_changes.begin(); it != tail.direct_changes.end();it++)
	{
		direct_changes.push_back(*it);
	}
}

bool Segment::hit_check(const Segment& segment) const &
{
	return shape.getGlobalBounds().intersects(segment.get_shape().getGlobalBounds());
}