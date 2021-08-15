#include "EditorState.h"

#include "../Util/Util.h"

EditorState::EditorState(Ref<sf::RenderWindow> window)
	: State(window), level(MakeRef<Level>(window))
{
}

EditorState::~EditorState()
{
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