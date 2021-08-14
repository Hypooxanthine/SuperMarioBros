#include "Level.h"

#include <fstream>
#include <sstream>

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

		//TODO : handling comment lines in levels.txt

		std::string line;
		while (std::getline(maps, line))
		{
			if (line.find(level)) //Level header found
			{
				LOG_INFO("Level " + level + " found.");
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
		setTile(i, height, *GenTile(TileType(tile)));

		i++;
	}

	std::cout << "\n";

	height++;
}

void Level::render()
{
}
