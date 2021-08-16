#pragma once

#include "Tile.h"
#include "Rock.h"
#include "Empty.h"

Tile* GenTile(const TileType& type, Ref<sf::RenderWindow> window);