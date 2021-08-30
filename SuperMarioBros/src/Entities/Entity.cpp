#include "Entity.h"

Entity::Entity(Ref<sf::RenderWindow> window)
	: Drawable(window)
{}

void Entity::move(const sf::Vector2f& offset)
{
	position += offset;
}

void Entity::move(const float& dx, const float& dy)
{
	move(sf::Vector2f(dx, dy));
}