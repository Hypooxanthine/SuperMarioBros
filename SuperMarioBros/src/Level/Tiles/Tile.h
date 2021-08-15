#pragma once

#include "../../Core/Base.h"

#define TILE_INIT_DEF \
public:\
	virtual sf::Sprite& getSprite() const override;\
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

class Tile
{
public:
	Tile(const bool& solid, const sf::Vector2i& position);
	Tile(const bool& solid);
	Tile();

	//Getters
	inline bool isSolid() { return solid; }
	static sf::Texture& getSpriteSheet();
	virtual sf::Sprite& getSprite() const = 0;

	//Setter
	inline void setSolid(const bool& value) { solid = value; }
	void setPosition(const sf::Vector2i& position);

	//Operators

protected:
	bool solid;

	sf::Vector2f position;
};

