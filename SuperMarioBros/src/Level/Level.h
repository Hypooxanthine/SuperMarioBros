#pragma once

#include "../Core/Base.h"
#include "Tiles/Tiles.h"

class Level
{
public:
	Level(Ref<sf::RenderWindow> window);
	virtual ~Level();

	void setTile(const size_t& x, const size_t& y, Tile* tile);

	Tile& getTile(const size_t& x, const size_t& y) const;

	bool load(const std::string& level);
	static std::vector<std::string> getLevelsList();

	inline const bool& isLoaded() { return loaded; }

	void render();

	void highlight(const size_t& x, const size_t& y);
	void stopHighlight(const size_t& x, const size_t& y);

private:
	void parseLine(const std::string& line);

	static inline const std::string path = "Resources/levels.txt";

	bool loaded;

	std::string name;
	size_t width, height;
	std::vector<Tile*> tiles;

	Ref<sf::RenderWindow> window;
};

