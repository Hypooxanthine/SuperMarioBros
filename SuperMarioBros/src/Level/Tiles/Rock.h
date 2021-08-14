#pragma once

#include "Tile.h"

class Rock : public Tile
{
	TILE_INIT_DEF
public:
	Rock() : Tile(true) {};
};

