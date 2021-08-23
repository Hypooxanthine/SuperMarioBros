#pragma once

#include "Tile.h"

#include "Empty.h"

#include "Rock.h"
#include "Stone.h"
#include "Brick.h"
#include "Mystery.h"

#include "LittleBushL.h"
#include "LittleBushM.h"
#include "LittleBushR.h"

#include "BigBushL.h"
#include "BigBushBlack.h"
#include "BigBushEmpty.h"
#include "BigBushR.h"
#include "BigBushT.h"

#include "CloudTL.h"
#include "CloudTM.h"
#include "CloudTR.h"
#include "CloudBL.h"
#include "CloudBM.h"
#include "CloudBR.h"

Ref<Tile> GenTile(const TileType& type, Ref<sf::RenderWindow> window);