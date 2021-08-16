#include "EditorState.h"

#include "../Util/Util.h"

EditorState::EditorState(Ref<sf::RenderWindow> window)
	: State(window), level(MakeRef<Level>(window)), cursorTile(nullptr), activeTile(nullptr)
{
}

EditorState::~EditorState()
{
	level->save();
}

void EditorState::init()
{
	LOG_TRACE("Initialization of EditorState.");

	std::cout << "What to do ?\n"
		<< "    1. Open a level\n"
		<< "    2. Create a level\n";
	size_t in = getUserIntRange("Choice", 1, 2);

	switch (in)
	{
	case 1:
		openLevel();
		break;
	case 2:
		break;
	default:
		break;
	}
}

void EditorState::update(const float& dt)
{
	static size_t xPos = 0, yPos = 0, xPosOld = 0, yPosOld = 0;
	static const auto& view = window->getView();

	xPosOld = xPos;
	yPosOld = yPos;

	const auto& mousePos = sf::Mouse::getPosition(*window);

	xPos = size_t((view.getCenter().x + mousePos.x - view.getSize().x / 2.f) / (16 * 4));
	yPos = size_t((view.getCenter().y + mousePos.y - view.getSize().y / 2.f) / (16 * 4));

	if ((xPos != xPosOld || yPos != yPosOld) && xPos < level->getWidth() && yPos < level->getHeight())
	{
		if (cursorTile)
			cursorTile->setHighlight(false);

		cursorTile = &level->getTile(xPos, yPos);
		
		if (cursorTile)
			cursorTile->setHighlight(true);
	}

	float tilesPerSecond = 15.f * 16.f * 4.f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		moveView(sf::Vector2f(-tilesPerSecond * dt, 0));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		moveView(sf::Vector2f(tilesPerSecond * dt, 0));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		moveView(sf::Vector2f(0.f, tilesPerSecond * dt));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		moveView(sf::Vector2f(0.f, -tilesPerSecond * dt));

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		level->setTile(xPos, yPos, GenTile(TileType::Rock, window));
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		level->setTile(xPos, yPos, GenTile(TileType::Empty, window));
}

void EditorState::render()
{
	if (level->isLoaded())
		level->render();
}

void EditorState::openLevel()
{
	auto levels = Level::getLevelsList();

	if (levels.size() > 0)
	{
		std::cout << "Available levels :\n";

		for (size_t i = 0; i < levels.size(); i++)
		{
			std::cout << "    " << i + 1 << ". " << levels[i] << "\n";
		}

		size_t in = getUserIntRange("Level to open", 1, levels.size());

		level->load(levels[in - 1]);
	}
}

void EditorState::moveView(const sf::Vector2f& delta)
{
	static const auto& view = window->getView();
	sf::View newView = sf::View(view.getCenter() + delta, view.getSize());
	const auto& center = newView.getCenter();
	const auto& size = newView.getSize();

	//Clamping view to borders of the level
	if (center.x - size.x / 2.f < 0)
		newView.setCenter(sf::Vector2f(size.x / 2.f, center.y));
	if (center.y - size.y / 2.f < 0)
		newView.setCenter(sf::Vector2f(center.x, size.y / 2.f));
	if (center.x + size.x / 2.f > level->getWidth() * 16.f * 4.f)
		newView.setCenter(sf::Vector2f(level->getWidth() * 16.f * 4.f - size.x / 2.f, center.y));
	if (center.y + size.y / 2.f > level->getHeight() * 16.f * 4.f)
		newView.setCenter(sf::Vector2f(center.x, level->getHeight() * 16.f * 4.f - size.y / 2.f));

	window->setView(newView);
}
