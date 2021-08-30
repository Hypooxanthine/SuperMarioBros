#pragma once

#include "../Core/Base.h"
#include "../Drawable.h"

class Entity : public Drawable
{
public:
	Entity(Ref<sf::RenderWindow> window);

	void move(const sf::Vector2f& offset);
	void move(const float& dx, const float& dy);
};

