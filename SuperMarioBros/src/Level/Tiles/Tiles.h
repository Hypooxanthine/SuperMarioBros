#pragma once

#include "Tile.h"
#include "Rock.h"
#include "Empty.h"
#include "Brick.h"
#include "Mystery.h"

Ref<Tile> GenTile(const TileType& type, Ref<sf::RenderWindow> window);