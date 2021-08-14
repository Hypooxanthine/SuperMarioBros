#pragma once

#include "Tile.h"
#include "Rock.h"
#include "Empty.h"

enum class TileType
{
	Empty = 0,

	Rock = 1,
	Stone = 2,
};

Ref<Tile> GenTile(const TileType& type);