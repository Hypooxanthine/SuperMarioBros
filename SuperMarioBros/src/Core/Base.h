#pragma once

/* Main STL libraries. */
#include <iostream>
#include <memory>
#include <functional>

/* SFML graphic component. */
#include <SFML/Graphics.hpp>

/* Logging. */
#include "Log.h"

// We will be using shared pointers a lot. Shared pointers are not this expensive for a single referenced
// pointer compared to unique pointers, so we can use shared pointers by default to make the code easier to read.
template<typename T>
using Ref = std::shared_ptr<T>;
template<typename T, typename ... Args>
constexpr Ref<T> MakeRef(Args&& ... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}