#include "Tiles.h"

Ref<Tile> GenTile(const TileType& type, Ref<sf::RenderWindow> window)
{
	Ref<Tile> out = nullptr;

	switch (type)
	{
	case TileType::Empty:
		out = MakeRef<Empty>(window);
		break;
	case TileType::Rock:
		out = MakeRef<Rock>(window);
		break;
	default:
		break;
	}

	return out;
}
