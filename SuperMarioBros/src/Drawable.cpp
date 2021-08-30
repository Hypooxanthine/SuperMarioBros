#include "Drawable.h"

Drawable::Drawable(Ref<sf::RenderWindow> window)
	: window(window)
{
}

void Drawable::render() const
{
	getSprite().setPosition(position);
	window->draw(getSprite());
}

void Drawable::setPosition(const sf::Vector2f pos)
{
	position = pos;
}

void Drawable::setPosition(const float& x, const float& y)
{
	setPosition(sf::Vector2f(x, y));
}

