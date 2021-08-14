#pragma once

#include "../../Core/Base.h"

#define TILE_INIT_DEF \
public:\
	virtual sf::Sprite& getSprite() override;\
private:\
	static sf::Sprite sprite;

#define TILE_INIT_IMP(tile, x, y) \
sf::Sprite& tile::getSprite()\
{\
	static bool initialized = false;\
	static sf::Sprite sprite;\
\
	if (!initialized)\
	{\
		sprite.setTexture(Tile::getSpriteSheet());\
		sprite.setTextureRect(sf::IntRect(x, y, 16, 16));\
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
	virtual sf::Sprite& getSprite() = 0;

	//Setter
	inline void setSolid(const bool& value) { solid = value; }
	void setPosition(const sf::Vector2i& position);

	//Operators

protected:
	bool solid;

	sf::Vector2f position;
};

