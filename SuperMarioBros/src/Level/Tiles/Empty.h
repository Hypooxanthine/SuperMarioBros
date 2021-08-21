#pragma once

#include "Tile.h"

class Empty : public Tile
{
	TILE_INIT_DEF(Empty)
public:
	virtual void render() const override;
};

