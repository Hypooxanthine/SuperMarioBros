#pragma once

#include "../../Core/Base.h"

#define TILE_INIT_DEF(tile) \
public:\
	using Type = tile;\
	tile(Ref<sf::RenderWindow> window) : Tile(window) {}\
	virtual sf::Sprite& getSprite() const override;\
	virtual const TileType& getType() const override { static TileType type = TileType::tile; return type; }\

#define TILE_INIT_IMP(tile, x, y) \
sf::Sprite& tile::getSprite() const\
{\
	static bool initialized = false;\
	static sf::Sprite sprite;\
\
	if (!initialized)\
	{\
		LOG_TRACE("Initialization of {} sprite.", #tile);\
		sprite.setTexture(Tile::getSpriteSheet());\
		sprite.setTextureRect(sf::IntRect(x * 16, y * 16, 16, 16));\
		sprite.setScale(sf::Vector2f(4.f, 4.f));\
		initialized = true;\
	}\
\
	return sprite;\
}

enum class TileType
{
	Empty = 0,

	Rock,
	Stone,
	Brick,
	Mystery,

	LittleBushL,
	LittleBushM,
	LittleBushR,

	BigBushL,
	BigBushM,
	BigBushR,
	BigBushT,

	CloudTL,
	CloudTM,
	CloudTR,
	CloudBL,
	CloudBM,
	CloudBR,

	PipeTL,
	PipeTR,
	PipeL,
	PipeR,

	FlagT,
	FlagM,

	CastleEntryM,
	CastleEntryL,
	CastleEntryR,
	CastleEntryT,
	CastleWallEmpty,
	CastleWallFilled,
};

class Tile
{
public:
	using type = Tile;
	Tile(Ref<sf::RenderWindow> window);

	inline void setHighlight(const bool& highlight) { this->highlight = highlight; }
	virtual void render() const;

	//Getters
	inline bool isSolid() { return solid; }
	static sf::Texture& getSpriteSheet();
	virtual sf::Sprite& getSprite() const = 0;
	virtual const TileType& getType() const = 0;

	//Setter
	inline void setSolid(const bool& value) { solid = value; }
	inline void setPosition(const sf::Vector2f& position) { this->position = position; }

	//Operators

protected:
	Ref<sf::RenderWindow> window;
	bool highlight;
	bool solid;

	sf::Vector2f position;
};

