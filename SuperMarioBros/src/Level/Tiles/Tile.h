#pragma once

#include "../../Core/Base.h"

#define TILE_INIT_DEF(tile) \
public:\
	using Type = tile;\
	virtual sf::Sprite& getSprite() const override;\
	tile(Ref<sf::RenderWindow> window) : Tile(window) {}\
	virtual TileType& getType() override { static TileType type = TileType::tile; return type; }\
private:\
	static sf::Sprite sprite;

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
		sprite.setTextureRect(sf::IntRect(x, y, 16, 16));\
		sprite.setScale(sf::Vector2f(4.f, 4.f));\
		initialized = true;\
	}\
\
	return sprite;\
}

enum class TileType
{
	Empty = 0,

	Rock = 1,
	Stone = 2,
};

class Tile
{
public:
	using type = Tile;
	Tile(Ref<sf::RenderWindow> window);

	inline void setHighlight(const bool& highlight) { this->highlight = highlight; }
	void render() const;

	//Getters
	inline bool isSolid() { return solid; }
	static sf::Texture& getSpriteSheet();
	virtual sf::Sprite& getSprite() const = 0;
	sf::RectangleShape& getFrame() const;
	virtual TileType& getType() = 0;

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

