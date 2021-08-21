#include "Empty.h"

TILE_INIT_IMP(Empty, 0, 0)

void Empty::render() const
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

	frame.setPosition(position);
	if (highlight)
		window->draw(frame);
}