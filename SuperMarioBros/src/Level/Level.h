#pragma once

#include "../Core/Base.h"
#include "Tiles/Tiles.h"

class Level
{
public:
	Level(Ref<sf::RenderWindow> window);

	void setTile(const size_t& x, const size_t& y, Tile* tile);

	const Tile& getTile(const size_t& x, const size_t& y) const;

	bool load(const std::string& level);
	static std::vector<std::string> getLevelsList();
	void parseLine(const std::string& line);

	inline const bool& isLoaded() { return loaded; }

	void render();

private:
	static inline const std::string path = "Resources/levels.txt";

	bool loaded;

	size_t width, height;
	std::vector<Tile*> tiles;

	Ref<sf::RenderWindow> window;
};

