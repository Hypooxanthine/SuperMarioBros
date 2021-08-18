#pragma once

#include "../Core/Base.h"
#include "Tiles/Tiles.h"

class Level
{
public:
	Level(Ref<sf::RenderWindow> window);
	virtual ~Level();

	void setTile(const size_t& x, const size_t& y, Ref<Tile> tile);

	Ref<Tile> getTile(const size_t& x, const size_t& y) const;
	inline size_t getWidth() { return width; }
	inline size_t getHeight() { return height; }

	bool load(const std::string& level);
	static std::vector<std::string> getLevelsList();
	bool save() const;

	void create(const std::string& name);

	inline const bool& isLoaded() { return loaded; }

	void render();

	void highlight(const size_t& x, const size_t& y);
	void stopHighlight(const size_t& x, const size_t& y);

private:
	void parseLine(const std::string& line);
	std::string getLine(const size_t& line) const;
	void writeLevel(std::ofstream& file) const;

	static inline const std::string pathIn = "Resources\\levels.txt";
	static inline const std::string pathOut = "Resources\\temp.txt";

	bool loaded;

	std::string name;
	size_t width, height;
	std::vector<Ref<Tile>> tiles;

	Ref<sf::RenderWindow> window;
};

