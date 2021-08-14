#pragma once

#include "Tile.h"

class Empty : public Tile
{
	TILE_INIT_DEF
public:
	Empty() : Tile(false) {}
};

