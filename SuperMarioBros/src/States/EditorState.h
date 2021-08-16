#pragma once

#include "State.h"
#include "../Level/Level.h"

class EditorState : public State
{
public:
	EditorState(Ref<sf::RenderWindow> window);
	virtual ~EditorState();

	virtual void init() override;
	virtual void update(const float& dt) override;
	virtual void render() override;

	void openLevel();

	void moveView(const sf::Vector2f& delta);

private:
	Ref<Level> level;
	Tile* cursorTile;
	Tile* activeTile;
};

