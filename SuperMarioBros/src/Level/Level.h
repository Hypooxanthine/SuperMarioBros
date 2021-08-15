#pragma once

#include "../Core/Base.h"
#include "Tiles/Tiles.h"

class Level
{
public:
	Level(const size_t& width, const size_t& height, Ref<sf::RenderWindow> window);
	Level(Ref<sf::RenderWindow> window);

	void setTile(const size_t& x, const size_t& y, Tile* tile);

	const Tile& getTile(const size_t& x, const size_t& y) const;

	bool load(const std::string& level);
	void parseLine(const std::string& line);

	void render();

private:
	size_t width, height;
	std::vector<Tile*> tiles;

	Ref<sf::RenderWindow> window;
};

