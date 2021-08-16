#include "Tiles.h"

Tile* GenTile(const TileType& type, Ref<sf::RenderWindow> window)
{
	Tile* out = nullptr;

	switch (type)
	{
	case TileType::Empty:
		out = new Empty(window);
		break;
	case TileType::Rock:
		out = new Rock(window);
		break;
	default:
		break;
	}

	return out;
}
