#pragma once

/* Main STL libraries. */
#include <iostream>
#include <memory>
#include <functional>
#include <optional>

/* SFML graphic component. */
#include <SFML/Graphics.hpp>

// We will be using shared pointers a lot. Shared pointers are not this expensive for a single referenced
// pointer compared to unique pointers, so we can use it by default to make the code easier to read.
template<typename T>
using Ref = std::shared_ptr<T>;
template<typename T, typename ... Args>
constexpr Ref<T> MakeRef(Args&& ... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}

/* Logging. */
#include "Log.h"

/* Utilities. */
#include "../Util/Util.h"

/* Consts. */
const float GLOBAL_SCALE = 4.f;
const float TILE_SIZE = 16.f * GLOBAL_SCALE;
const uint32_t LEVEL_TILES_X = 16;
const uint32_t LEVEL_TILES_Y = 15;

const uint32_t TOOLKIT_WIDTH = 100;
const float EDITOR_SPEED = 15.f * TILE_SIZE;
const float EDITOR_SPEED_FACTOR = 3.f;