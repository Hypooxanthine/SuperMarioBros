#include "TileSwapper.h"

TileSwapper::TileSwapper(Ref<sf::RenderWindow> window, const sf::Vector2f& size)
	: window(window), margin(20.f), selected(0), size(size)
{
	init();
}

void TileSwapper::render()
{
	for (Ref<Tile>& t : tiles)
		t->render();
}

const TileType& TileSwapper::getSelected() const
{
	return tiles[selected]->getType();
}

void TileSwapper::next()
{
	tiles[selected]->setHighlight(false);
	selected = (selected + 1) % tiles.size();
	tiles[selected]->setHighlight(true);
}

void TileSwapper::previous()
{
	tiles[selected]->setHighlight(false);
	selected = (selected + tiles.size() - 1) % tiles.size(); // Positive only
	tiles[selected]->setHighlight(true);
}

void TileSwapper::init()
{
	add(TileType::Rock);
	add(TileType::Stone);
	add(TileType::Brick);
	add(TileType::Mystery);

	add(TileType::LittleBushL);
	add(TileType::LittleBushM);
	add(TileType::LittleBushR);

	add(TileType::BigBushL);
	add(TileType::BigBushBlack);
	add(TileType::BigBushEmpty);
	add(TileType::BigBushR);
	add(TileType::BigBushT);

	add(TileType::CloudTL);
	add(TileType::CloudTM);
	add(TileType::CloudTR);
	add(TileType::CloudBL);
	add(TileType::CloudBM);
	add(TileType::CloudBR);
}

void TileSwapper::add(const TileType& t)
{
	auto tile = GenTile(t, window);
	tiles.push_back(tile);

	tile->setPosition(sf::Vector2f((size.x - TILE_SIZE) / 2.f, margin + (tiles.size() - 1) * (margin + TILE_SIZE)));
	if (tiles.size() - 1 == selected)
		tile->setHighlight(true);
}
