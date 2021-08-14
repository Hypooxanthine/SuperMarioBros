#include "Tile.h"

Tile::Tile(const bool& solid, const sf::Vector2i& position)
	: Tile(solid)
{
	setPosition(position);
}

Tile::Tile(const bool& solid)
	: solid(solid)
{}

Tile::Tile()
	: Tile(false)
{}

sf::Texture& Tile::getSpriteSheet()
{
	static bool initialized = false;
	static sf::Texture spriteSheet;

	if (!initialized)
	{
		spriteSheet.loadFromFile("Resources/spritesheet.png");
		initialized = true;
	}

	return spriteSheet;
}

void Tile::setPosition(const sf::Vector2i& position)
{
	this->position = sf::Vector2f(float(position.x * 16), float(position.y * 16));
}
