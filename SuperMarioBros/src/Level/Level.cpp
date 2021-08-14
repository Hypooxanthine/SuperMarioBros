#include "Level.h"

#include <fstream>

Level::Level(const size_t& width, const size_t& height, Ref<sf::RenderWindow> window)
	: width(width), height(height), tiles(nullptr), window(window)
{}

Level::Level(Ref<sf::RenderWindow> window)
	: Level(0, 0, window)
{
}

void Level::setTile(const size_t& x, const size_t& y, const Tile& tile)
{
	if(x < width && y < height)
		tiles[y * width + x] = tile;
}

void Level::setTile(const size_t& x, const size_t& y, Tile&& tile)
{
	if (x < width && y < height)
		tiles[y * width + x] = tile;
}

bool Level::load(const std::string& level)
{
	static std::string path = "Resources/levels.txt";

	std::ifstream maps;
	maps.open(path);

	if (maps.is_open())
	{
		LOG_INFO("Loaded \"" + path + "\" successfully.");

		maps.close();

		return true;
	}
	else
	{
		LOG_ERROR("Unable to open \"" + path + "\"");

		return false;
	}
}

void Level::render()
{
}
