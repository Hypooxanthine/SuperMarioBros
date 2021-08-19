#pragma once

#include "State.h"
#include "../Level/Level.h"

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

	void moveView(const sf::Vector2f& delta);

	template<class T>
	bool belongsToView(const sf::Vector2<T>& point) const;

private:
	Ref<Level> level;
	Ref<Tile> cursorTile;
	Ref<Tile> activeTile;

	sf::View levelView, toolkitView;
	sf::Vector2u levelSize, toolkitSize;
	sf::RectangleShape toolkitBackground;

	// Map movement
	float cameraSpeed;
};

