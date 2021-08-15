#include "Level.h"

#include <fstream>
#include <sstream>

Level::Level(const size_t& width, const size_t& height, Ref<sf::RenderWindow> window)
	: width(width), height(height), window(window)
{}

Level::Level(Ref<sf::RenderWindow> window)
	: Level(0, 0, window)
{
}

void Level::setTile(const size_t& x, const size_t& y, Tile* tile)
{
	if(x < width && y < height)
		tiles[y * width + x] = tile;
}

const Tile& Level::getTile(const size_t& x, const size_t& y) const
{
	return *tiles[y * width + x];
}

bool Level::load(const std::string& level)
{
	static std::string path = "Resources/levels.txt";

	std::ifstream maps;
	maps.open(path);

	if (maps.is_open())
	{
		LOG_INFO("Loaded \"" + path + "\" successfully.");

		//TODO : handling comment lines in levels.txt

		std::string line;
		while (std::getline(maps, line))
		{
			if (line.find(level)) //Level header found
			{
				LOG_INFO("Level " + level + " found.");

				std::stringstream size(line);
				size >> width >> height;
				LOG_TRACE("width : {}, height : {}", width, height);
				tiles.reserve(width * height);

				std::getline(maps, line);

				while (true)
				{
					parseLine(line);

					if (!std::getline(maps, line))
						break;

					if (line.length() == 0)
						break;

				}

				LOG_INFO("Level loaded.");

				break;
			}
		}

		maps.close();

		return true;
	}
	else
	{
		LOG_ERROR("Unable to open \"" + path + "\"");

		return false;
	}
}

void Level::parseLine(const std::string& line)
{
	int tile = 0;
	size_t i = 0;
	std::stringstream liness(line);

	while (liness >> tile)
	{
		std::cout << tile << " ";
		tiles.push_back(GenTile(TileType(tile)));

		i++;
	}

	std::cout << "\n";
}

void Level::render()
{
	for (size_t y = 0; y < height; y++)
	{
		for (size_t x = 0; x < width; x++)
		{
			getTile(x, y).getSprite().setPosition(sf::Vector2f((float)(x * 16 * 4), (float)(y * 16 * 4)));
			window->draw(getTile(x, y).getSprite());
		}
	}
}
