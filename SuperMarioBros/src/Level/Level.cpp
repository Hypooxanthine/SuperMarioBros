#include "Level.h"

#include <fstream>
#include <sstream>

Level::Level(Ref<sf::RenderWindow> window)
	: width(0), height(0), window(window), loaded(false)
{}

Level::~Level()
{
	for (Tile* t : tiles)
		delete t;
}

void Level::setTile(const size_t& x, const size_t& y, Tile* tile)
{
	if (x < width && y < height)
	{
		delete tiles[y * width + x];
		tile->setPosition(sf::Vector2f((float)(x * 16 * 4), (float)(y * 16 * 4)));
		tiles[y * width + x] = tile;
	}
}

Tile& Level::getTile(const size_t& x, const size_t& y) const
{
	if (x < width && y < height)
		return *tiles[y * width + x];
	else
	{
		if (x > width && y < height)
			return getTile(width - 1, y);
		else if (x > width && y > height)
			return getTile(width - 1, height - 1);
		else
			return getTile(x, y - 1);
	}
}

bool Level::load(const std::string& level)
{
	std::ifstream maps;
	maps.open(pathIn);

	if (maps.is_open())
	{
		LOG_INFO("Loaded \"" + pathIn + "\" successfully.");

		//TODO : handling comment lines in levels.txt

		std::string line;
		while (std::getline(maps, line))
		{
			if (line.find(level) != std::string::npos) //Level header found
			{
				LOG_INFO("Level " + level + " found.");
				name = level;

				std::getline(maps, line);
				std::stringstream size(line);
				size >> width >> height;
				LOG_TRACE("width : {}, height : {}", width, height);
				tiles.reserve(width * height);

				while (std::getline(maps, line))
				{
					if (line.length() == 0)
						break;

					parseLine(line);
				}

				loaded = true;
				LOG_INFO("Level loaded.");

				break;
			}
		}

		maps.close();

		return true;
	}
	else
	{
		LOG_ERROR("Unable to open \"" + pathIn + "\"");

		return false;
	}
}

std::vector<std::string> Level::getLevelsList()
{
	std::vector<std::string> out;

	std::ifstream maps;
	maps.open(pathIn);

	if (maps.is_open())
	{
		LOG_INFO("Loaded \"" + pathIn + "\" successfully.");

		//TODO : handling comment lines in levels.txt

		std::string line;
		while (std::getline(maps, line))
		{
			if (line.find("name") != std::string::npos) //Level name line found
			{
				out.push_back(line.substr(5));
			}
		}

		maps.close();
	}
	else
	{
		LOG_ERROR("Unable to open \"" + pathIn + "\"");
	}

	return out;
}

bool Level::save() const
{
	std::fstream maps;
	std::ofstream temp; //Temporary file that will be the new save file at the end
	maps.open(pathIn);

	if (maps.is_open())
	{
		LOG_INFO("{} opened successfuly.", pathIn);

		temp.open(pathOut, std::fstream::out); //Creating the temporary file

		std::string line;

		while (std::getline(maps, line)) //Copying all lines...
		{

			if (line.find(name) != std::string::npos) //Until we find the level name
			{
				writeLevel(temp); //Writing level data
				break;
			}
			
			temp << line << "\n";
		}

		if (maps.peek() == -1)
		{
			LOG_INFO("{} has not been found to be rewritten. Creating data...", name);

			writeLevel(temp);
		}

		while (std::getline(maps, line)) //We skip all the previous level data
		{
			if (line == "")
			{
				temp << line;
				break;
			}
		}

		temp << "\n";

		while (std::getline(maps, line)) //We can copy the remaining lines
			temp << line << "\n";

		temp.close();
		maps.close();

		std::remove(pathIn.data());
		std::rename(pathOut.data(), pathIn.data());
		std::remove(pathOut.data());

		LOG_INFO("Level {} saved.", name);
		return true;
	}
	else
		return false;
}

void Level::parseLine(const std::string& line)
{
	int tile = 0;
	size_t i = 0;
	std::stringstream liness(line);

	while (liness >> tile)
	{
		std::cout << tile << " ";
		Tile* t = GenTile(TileType(tile), window);
		t->setPosition(sf::Vector2f((float)(i * 16 * 4), (float)((tiles.size() + 1 - i) / width * 16 * 4)));
		tiles.push_back(t);

		i++;
	}

	std::cout << "\n";
}

std::string Level::getLine(const size_t& line) const
{
	std::string out = "";

	for (size_t i = 0; i < width; i++)
		out += " " + std::to_string((int)tiles[width * line + i]->getType());

	out += "\n";

	return out;
}

void Level::writeLevel(std::ofstream& file) const
{
	file << "name " << name << "\n";
	file << width << " " << height << "\n";

	for (size_t i = 0; i < height; i++)
		file << getLine(i);
}

void Level::render()
{
	// Rendering optimization
	size_t minX = 0, maxX = width, minY = 0, maxY = height;

	const auto& view = window->getView();

	minX = int((view.getCenter().x - view.getSize().x / 2) / (16 * 4));
	maxX = int((view.getCenter().x + view.getSize().x / 2) / (16 * 4));
	minY = int((view.getCenter().y - view.getSize().y / 2) / (16 * 4));
	maxY = int((view.getCenter().y + view.getSize().y / 2) / (16 * 4));

	if (maxX < width)
		maxX++;
	if (maxY < height)
		maxY++;

	if (maxX > width)
		maxX = width;
	if (maxY > height)
		maxY = height;

	for (size_t y = minY; y < maxY; y++)
	{
		for (size_t x = minX; x < maxX; x++)
		{
			getTile(x, y).render();
		}
	}
}

void Level::highlight(const size_t& x, const size_t& y)
{
	getTile(x, y).setHighlight(true);
}

void Level::stopHighlight(const size_t& x, const size_t& y)
{
	getTile(x, y).setHighlight(false);
}
