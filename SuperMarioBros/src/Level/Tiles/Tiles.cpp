#include "Tiles.h"

#define FEED_TILESET(type) tileset[TileType::type] = &createInstance<type>;

template<typename T>
Ref<Tile> createInstance(Ref<sf::RenderWindow> window)
{
	return MakeRef<T>(window);
}

Ref<Tile> GenTile(const TileType& type, Ref<sf::RenderWindow> window)
{
	/* We create a mapping : each enum allows to create a Ref of its specific Tile derived class.
	*  To do this, each TileType value corresponds to a function pointer in the map that constructs the appropriate Ref.
	*  Finally, we just have to call the function at the specified TileType key in the map to create the Ref this function is expected to return. */

	using createInstancePtr = std::function<Ref<Tile>(Ref<sf::RenderWindow>)>; // For readability purpose

	static bool init = false;
	static std::map<TileType, createInstancePtr> tileset; // The mapping is unique, that's why it's set to static variable.

	if (!init)
	{
		FEED_TILESET(Empty);

		FEED_TILESET(Rock);
		FEED_TILESET(Stone);
		FEED_TILESET(Brick);
		FEED_TILESET(Mystery);

		FEED_TILESET(LittleBushL);
		FEED_TILESET(LittleBushM);
		FEED_TILESET(LittleBushR);

		FEED_TILESET(BigBushL);
		FEED_TILESET(BigBushBlack);
		FEED_TILESET(BigBushEmpty);
		FEED_TILESET(BigBushR);
		FEED_TILESET(BigBushT);

		FEED_TILESET(CloudTL);
		FEED_TILESET(CloudTM);
		FEED_TILESET(CloudTR);
		FEED_TILESET(CloudBL);
		FEED_TILESET(CloudBM);
		FEED_TILESET(CloudBR);

		FEED_TILESET(PipeTL);
		FEED_TILESET(PipeTR);
		FEED_TILESET(PipeL);
		FEED_TILESET(PipeR);

		FEED_TILESET(FlagT);
		FEED_TILESET(FlagM);

		FEED_TILESET(CastleEntryM);
		FEED_TILESET(CastleEntryL);
		FEED_TILESET(CastleEntryR);
		FEED_TILESET(CastleEntryT);
		FEED_TILESET(CastleWallEmpty);
		FEED_TILESET(CastleWallFilled);
		FEED_TILESET(CastleBlock);

		init = true;
	}

	return tileset[type](window);
}
