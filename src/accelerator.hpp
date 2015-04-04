#pragma once
#include <glm/glm.hpp>

class Accelerator
{
    public:
        glm::vec2 get(glm::vec2 direction, float maxSpeed, const glm::vec2& currentVelocity, float maxAcc) const;
};
