#include "Tiles.h"

Ref<Tile> GenTile(const TileType& type)
{
	Ref<Tile> out = nullptr;

	switch (type)
	{
	case TileType::Empty:
		out = MakeRef<Empty>();
		break;
	case TileType::Rock:
		out = MakeRef<Rock>();
		break;
	default:
		break;
	}

	return out;
}
