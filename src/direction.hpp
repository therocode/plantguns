#pragma once
#include <glm/glm.hpp>

enum Direction {LEFT, RIGHT, UP, DOWN, NONE};

glm::vec2 toVector(Direction direction);
