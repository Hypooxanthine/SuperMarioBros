#pragma once

#include "Tiles/Tiles.h"

class TileSwapper
{
public:
	TileSwapper(Ref<sf::RenderWindow> window, const sf::Vector2f& size);

	inline void setMargin(const float& value) { margin = value; }

	void render();

	const TileType& getSelected() const;

	void next();
	void previous();

private:
	void updatePositions();

	Ref<sf::RenderWindow> window;
	sf::Vector2f size;

	void init();
	void add(const TileType& t);

	std::vector<Ref<Tile>> tiles;
	size_t selected;
	float margin;
	float firstPosition;
};

