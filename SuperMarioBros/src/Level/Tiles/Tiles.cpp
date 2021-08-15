#include "Tiles.h"

Tile* GenTile(const TileType& type)
{
	Tile* out = nullptr;

	switch (type)
	{
	case TileType::Empty:
		out = new Empty();
		break;
	case TileType::Rock:
		out = new Rock();
		break;
	default:
		break;
	}

	return out;
}
