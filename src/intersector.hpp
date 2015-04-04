#pragma once
#include <glm/glm.hpp>

class Intersector
{
    public:
        bool intersects(const glm::vec2& collAStart, const glm::vec2& collASize, const glm::vec2& collBStart, const glm::vec2& collBSize);
};
