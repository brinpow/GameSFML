#pragma once
#include <SFML/Graphics.hpp>
#include "config.h"
#include <list>
#include <cmath>
using namespace sf;

class Segment:public Drawable
{
	static float size;
	RectangleShape shape;

	Vector2f velocity;
	static float velocity_x;
	static float velocity_y;

	std::list<std::pair<Vector2f, Vector2f>> direct_changes;

public:
	Segment(float x, float y,const Color& color, float size=50.0f);

	void draw(RenderTarget& target, RenderStates state) const override;

	bool check_bounds();

	void update_head(std::list<Segment>&);

	void update();

	RectangleShape get_shape() const&;

	Vector2f get_postion() const &;

	void set_velocity(const Vector2f& velocity);

	void set_direct_changes(const Segment& tail);

	Vector2f get_velocity() const;

	bool hit_check(const Segment&) const&;
};

