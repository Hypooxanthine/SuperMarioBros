#include "Level.h"

#include <fstream>
#include <sstream>

Level::Level(Ref<sf::RenderWindow> window)
	: width(0), height(0), window(window), loaded(false), theme(Theme::Overworld)
{}

Level::~Level()
{}

void Level::setTile(const size_t& x, const size_t& y, Ref<Tile> tile)
{
	if (x < width && y < height)
	{
		tile->setPosition(sf::Vector2f((float)(x * TILE_SIZE), (float)(y * TILE_SIZE)));
		tiles[y * width + x] = tile;
	}
}

Ref<Tile> Level::getTile(const size_t& x, const size_t& y) const
{
	if (x < width && y < height)
		return tiles[y * width + x];
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
			if (line.substr(strlen("name ")) == level) //Level header found
			{
				LOG_INFO("Level " + level + " found.");
				name = level;

				std::getline(maps, line);
				std::stringstream size(line);
				size >> width >> height;
				LOG_TRACE("width : {}, height : {}", width, height);
				tiles.reserve(width * height);

				std::getline(maps, line);
				theme = Theme(line.at(strlen("theme ")) - '0');
				LOG_TRACE("Level theme : {}", theme);

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
			if (line.find("name ") != std::string::npos) //Level name line found
			{
				out.push_back(line.substr(strlen("name ")));
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
	if (!loaded)
		return false;

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
				LOG_INFO("{} found. Overriding save data.", name);

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

void Level::create(const std::string& name)
{
	LOG_INFO("Creating level {}.", name);

	std::ofstream file;

	file.open(pathIn, std::fstream::out|std::fstream::app);

	if (file.is_open())
	{
		LOG_INFO("{} opened successfuly.", pathIn);

		// Creating default level
		file << "name " << name << "\n";
		file << "224 30\n";
		file << "theme 0\n";

		for (size_t y = 0; y < 30; y++)
		{
			for (size_t x = 0; x < 224; x++)
			{
				file << " " << (y > 27 ? "1" : "0");
			}

			file << "\n";
		}

		file << "\n";

		file.close();
	}
	else
		LOG_ERROR("Couldn't open file {}.", pathIn);
}

void Level::parseLine(const std::string& line)
{
	int tile = 0;
	size_t i = 0;
	std::stringstream liness(line);

	while (liness >> tile)
	{
		auto t = GenTile(TileType(tile), window);
		t->setPosition(sf::Vector2f((float)(i * TILE_SIZE), (float)((tiles.size() + 1 - i) / width * TILE_SIZE)));
		tiles.push_back(t);

		i++;
	}
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
	file << "theme " << (int)theme << "\n";

	for (size_t i = 0; i < height; i++)
		file << getLine(i);
}

sf::Color Level::getBackgroundColor()
{
	switch (theme)
	{
	case Theme::Overworld:
		return sf::Color(92, 148, 252);
		break;
	case Theme::Cave:
		return sf::Color::Black;
		break;
	default:
		return sf::Color::Red;
		break;
	}
}

void Level::render()
{
	// Rendering optimization : we only draw tiles we can see.
	const auto& view = window->getView();

	size_t minX = int((view.getCenter().x - view.getSize().x / 2) / TILE_SIZE);
	size_t maxX = int((view.getCenter().x + view.getSize().x / 2) / TILE_SIZE);
	size_t minY = int((view.getCenter().y - view.getSize().y / 2) / TILE_SIZE);
	size_t maxY = int((view.getCenter().y + view.getSize().y / 2) / TILE_SIZE);

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
			getTile(x, y)->render();
		}
	}
}

void Level::highlight(const size_t& x, const size_t& y)
{
	getTile(x, y)->setHighlight(true);
}

void Level::stopHighlight(const size_t& x, const size_t& y)
{
	getTile(x, y)->setHighlight(false);
}
