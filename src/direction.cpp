#include "direction.hpp"

glm::vec2 toVector(Direction direction)
{
    if(direction == LEFT)
        return glm::vec2(-1.0f, 0.0f);
    else if(direction == RIGHT)
        return glm::vec2(1.0f, 0.0f);
    else if(direction == UP)
        return glm::vec2(0.0f, -1.0f);
    else if(direction == DOWN)
        return glm::vec2(0.0f, 1.0f);

    return glm::vec2();
}
