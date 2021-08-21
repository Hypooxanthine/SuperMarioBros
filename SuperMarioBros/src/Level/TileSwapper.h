#pragma once

#include "Tiles/Tiles.h"

class TileSwapper
{
public:
	TileSwapper(Ref<sf::RenderWindow> window);

	inline void setMargin(const float& value) { margin = value; }

	void render();

	const TileType& getSelected() const;

	void next();
	void previous();

private:
	Ref<sf::RenderWindow> window;

	void init();
	void add(const TileType& t);

	std::vector<Ref<Tile>> tiles;
	size_t selected;
	float margin;
};

