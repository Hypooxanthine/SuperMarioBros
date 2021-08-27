#include "EditorState.h"

#include "../Util/Util.h"

EditorState::EditorState(Ref<sf::RenderWindow> window)
	: State(window), level(MakeRef<Level>(window)), cursorTile(nullptr), activeTile(nullptr),
	levelView(sf::View(sf::FloatRect(0.f, (float)(TILE_SIZE * 15), (float)(TILE_SIZE * LEVEL_TILES_X), (float)(TILE_SIZE * LEVEL_TILES_Y)))),
	toolkitSize(sf::Vector2u(TOOLKIT_WIDTH, window->getSize().y)), swapper(window, (sf::Vector2f)toolkitSize), speedCamera(false)
{
	
}

EditorState::~EditorState()
{
	window->setSize(levelSize);

	level->save();
}

void EditorState::init()
{
	LOG_TRACE("Initialization of EditorState.");

	editorSelector();

	levelSize = window->getSize();

	window->setSize(sf::Vector2u(levelSize.x + toolkitSize.x, window->getSize().y));
	levelView.setViewport(sf::FloatRect(0.f, 0.f, (float)levelSize.x / (levelSize.x + toolkitSize.x), 1.f));
	toolkitView.setViewport(sf::FloatRect((float)levelSize.x / (levelSize.x + toolkitSize.x), 0.f, 1.f, 1.f));
	toolkitView.setSize(sf::Vector2f((float)(toolkitSize.x + levelSize.x), (float)toolkitSize.y));
	toolkitView.setCenter(toolkitView.getSize() / 2.f);

	toolkitBackground.setSize((sf::Vector2f)toolkitSize);
	toolkitBackground.setFillColor(sf::Color(100, 100, 100));
	toolkitBackground.setPosition(0.f, 0.f);
}

void EditorState::updateEvents(sf::Event& e, const float& dt)
{
	if (e.type == sf::Event::KeyPressed)
	{
		switch (e.key.code)
		{
		case sf::Keyboard::Up:
			swapper.previous();
			break;
		case sf::Keyboard::Down:
			swapper.next();
			break;
		case sf::Keyboard::LShift:
			speedCamera = true;
			break;
		case sf::Keyboard::Escape:
			endState();
			break;
		}
	}

	if (e.type == sf::Event::KeyReleased)
	{
		switch (e.key.code)
		{
		case sf::Keyboard::LShift:
			speedCamera = false;
			break;
		}
	}

	if (e.type == sf::Event::MouseWheelMoved)
		e.mouseWheel.delta > 0 ? swapper.previous() : swapper.next();
}

void EditorState::update(const float& dt)
{
	// Showing FPS each second
	/*static sf::Clock c;

	if (c.getElapsedTime().asSeconds() > 1.f)
	{
		LOG_INFO("DT  : {}", dt);
		LOG_INFO("FPS : {}", 1.f / dt);
		c.restart();
	}*/
	
	static size_t xPos = 0, yPos = 0, xPosOld = 0, yPosOld = 0; //Static because we want these variables to last more than this scope. They are not member variables because they are not used anywhere else than here for now.

	const auto& mousePos = sf::Mouse::getPosition(*window);
	const auto& mousePosWorld = window->mapPixelToCoords(mousePos);

	// These booleans allow to know if cursor just entered the level view. When the cursor exit level view, xPos and yPos don't update.
	// Then, by coming back into level view, on the same tile, xPos = xPosOld, and yPos = yPosOld, and the highlighting wouldn't work
	// correctly. These booleans avoid this unwanted behaviour.
	static bool outOfView = false;
	static bool justEnteredView = false;

	// Updating mouse positions
	if (belongsToView(mousePosWorld))
	{
		// Updating old mouse positions
		xPosOld = xPos;
		yPosOld = yPos;

		xPos = size_t((levelView.getCenter().x + mousePos.x - levelView.getSize().x / 2.f) / TILE_SIZE);
		yPos = size_t((levelView.getCenter().y + mousePos.y - levelView.getSize().y / 2.f) / TILE_SIZE);

		if (outOfView)
			justEnteredView = true;
		outOfView = false;
	}
	else
	{
		outOfView = true;
		justEnteredView = false;
	}

	// Highlighting the correct tile when cursor is moving inside the view
	if ((xPos != xPosOld || yPos != yPosOld || justEnteredView) // Update highlighting when cursor just entered level view on the same tile it had exited.
		&& belongsToView(mousePosWorld))
	{
		if (cursorTile)
			cursorTile->setHighlight(false);

		cursorTile = level->getTile(xPos, yPos);
		
		if (cursorTile)
			cursorTile->setHighlight(true);
	}

	// Unhighlight highlighted tile when cursor leaves level view
	if (!belongsToView(mousePosWorld))
	{
		if (cursorTile)
			cursorTile->setHighlight(false);

		cursorTile = nullptr;
	}

	// Camera movement
	if (window->hasFocus())
	{
		// Applying a multi
		float speed = EDITOR_SPEED * (speedCamera ? EDITOR_SPEED_FACTOR : 1.f);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			moveView(sf::Vector2f(-speed * dt, 0));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			moveView(sf::Vector2f(speed * dt, 0));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			moveView(sf::Vector2f(0.f, speed * dt));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			moveView(sf::Vector2f(0.f, -speed * dt));
	}

	// Placing/removing tiles
	if (belongsToView(mousePosWorld) && window->hasFocus())
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			auto newTile = GenTile(swapper.getSelected(), window);
			level->setTile(xPos, yPos, newTile);
			cursorTile = newTile;
			cursorTile->setHighlight(true);
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			auto newTile = GenTile(TileType::Empty, window);
			level->setTile(xPos, yPos, newTile);
			cursorTile = newTile;
			cursorTile->setHighlight(true);
		}
	}
}

void EditorState::render()
{
	if (level->isLoaded())
	{
		// TODO : Drawing editor toolkit
		window->setView(toolkitView);
		window->draw(toolkitBackground);
		swapper.render();

		// Drawing level
		window->setView(levelView);
		level->render();
	}
}

Ref<State> EditorState::getNextState() const
{
	return nullptr;
}

void EditorState::editorSelector()
{
	LOG_INFO("Entering the level editor selector.");

	std::cout << "What to do ?\n"
		<< "    1. Open a level\n"
		<< "    2. Create a level\n"
		<< "    3. Exit\n";
	size_t in = getUserIntRange("Choice", 1, 3);

	switch (in)
	{
	case 1:
		openLevel();
		break;
	case 2:
		createLevel();
		break;
	case 3:
	default:
		endState();
		break;
	}
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

		std::cout << "    " << levels.size() + 1 << ". Back to previous menu.\n";

		size_t in = getUserIntRange("Level to open", 1, levels.size() + 1);

		if (in - 1 < levels.size())
			level->load(levels[in - 1]);
		else
			editorSelector();
	}
	else
	{
		std::cout << "No level available. Please create one before opening it.\n";
		editorSelector();
	}
}

void EditorState::createLevel()
{
	std::string levelName;
	bool alreadyExists = true;

	while (alreadyExists)
	{
		levelName = getUserString("New level name");

		// Checking if the new level name isn't already used
		alreadyExists = false;
		for (const auto& name : level->getLevelsList())
		{
			if (name == levelName)
			{
				alreadyExists = true;
				std::cout << "Level \"" << levelName << "\" already exists, please type another name.\n";
			}
		}
	}

	level->create(levelName);
	editorSelector();
}

sf::Color EditorState::getBackgroundColor() const
{
	if (level->isLoaded())
		return level->getBackgroundColor();
	else
		return sf::Color(0, 0, 0);
}

void EditorState::moveView(const sf::Vector2f& delta)
{
	// Because we're getting center and size by reference, there is no need to initialize those variables more than once, at the first function call.
	static const auto& center = levelView.getCenter();
	static const auto& size = levelView.getSize();

	levelView.setCenter(levelView.getCenter() + delta);


	//Clamping view to borders of the level
	if (center.x - size.x / 2.f < 0)
		levelView.setCenter(sf::Vector2f(size.x / 2.f, center.y));
	if (center.y - size.y / 2.f < 0)
		levelView.setCenter(sf::Vector2f(center.x, size.y / 2.f));
	if (center.x + size.x / 2.f > level->getWidth() * TILE_SIZE)
		levelView.setCenter(sf::Vector2f(level->getWidth() * TILE_SIZE - size.x / 2.f, center.y));
	if (center.y + size.y / 2.f > level->getHeight() * TILE_SIZE)
		levelView.setCenter(sf::Vector2f(center.x, level->getHeight() * TILE_SIZE - size.y / 2.f));
}

template<class T>
bool EditorState::belongsToView(const sf::Vector2<T>& point) const
{
	return std::abs(point.x - levelView.getCenter().x) < levelView.getSize().x / 2.f
		&& std::abs(point.y - levelView.getCenter().y) < levelView.getSize().y / 2.f;
}