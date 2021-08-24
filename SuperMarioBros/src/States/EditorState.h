#pragma once

#include "State.h"
#include "../Level/Level.h"
#include "../Level/TileSwapper.h"

class EditorState : public State
{
public:
	EditorState(Ref<sf::RenderWindow> window);
	virtual ~EditorState();

	virtual void init() override;
	virtual void updateEvents(sf::Event& e, const float& dt) override;
	virtual void update(const float& dt) override;
	virtual void render() override;

	void editorSelector();

	void openLevel();
	void createLevel();

	virtual sf::Color getBackgroundColor() const override;

	void moveView(const sf::Vector2f& delta);

	template<class T>
	bool belongsToView(const sf::Vector2<T>& point) const;

private:
	Ref<Level> level;
	Ref<Tile> cursorTile;
	Ref<Tile> activeTile;

	// Views
	sf::View levelView, toolkitView;
	sf::Vector2u levelSize, toolkitSize;
	bool speedCamera;

	// Toolkit
	sf::RectangleShape toolkitBackground;
	TileSwapper swapper;
};

