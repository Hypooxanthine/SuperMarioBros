#pragma once

#include "Tile.h"
#include "Rock.h"
#include "Empty.h"
#include "Brick.h"
#include "Mystery.h"

#include "LittleBushL.h"
#include "LittleBushM.h"
#include "LittleBushR.h"

#include "BigBushL.h"
#include "BigBushM.h"
#include "BigBushR.h"
#include "BigBushT.h"

#include "CloudTL.h"
#include "CloudTM.h"
#include "CloudTR.h"
#include "CloudBL.h"
#include "CloudBM.h"
#include "CloudBR.h"

Ref<Tile> GenTile(const TileType& type, Ref<sf::RenderWindow> window);