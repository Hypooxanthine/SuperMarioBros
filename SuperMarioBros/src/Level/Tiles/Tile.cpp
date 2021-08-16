#include "Tile.h"

Tile::Tile(Ref<sf::RenderWindow> window)
	: window(window), highlight(false), solid(false)
{}

void Tile::render() const
{
	static sf::RectangleShape frame;
	static bool initialized = false;

	if (!initialized)
	{
		static float thickness = 4.f;
		frame.setSize(sf::Vector2f((float)(16 * 4), (float)(16 * 4)));
		frame.setOutlineThickness(-thickness);
		frame.setOutlineColor(sf::Color::Magenta);
		frame.setFillColor(sf::Color::Transparent);

		initialized = true;
	}

	getSprite().setPosition(position);
	frame.setPosition(position);
	window->draw(getSprite());
	if (highlight)
		window->draw(frame);
}

sf::Texture& Tile::getSpriteSheet()
{
	static bool initialized = false;
	static sf::Texture spriteSheet;

	if (!initialized)
	{
		LOG_TRACE("Loading spritesheet.");
		spriteSheet.loadFromFile("Resources/spritesheet.png");
		initialized = true;
	}

	return spriteSheet;
}
