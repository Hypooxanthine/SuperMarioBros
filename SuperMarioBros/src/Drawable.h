#pragma once

#include "Core/Base.h"

class Drawable
{
public:
	Drawable(Ref<sf::RenderWindow> window);

	virtual sf::Sprite& getSprite() const = 0;
	virtual void render() const;

	void setPosition(const sf::Vector2f pos);
	void setPosition(const float& x, const float& y);

protected:
	Ref<sf::RenderWindow> window;

	sf::Vector2f position;
};

