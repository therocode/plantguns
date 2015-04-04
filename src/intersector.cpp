#include "intersector.hpp"

bool Intersector::intersects(const glm::vec2& collAStart, const glm::vec2& collASize, const glm::vec2& collBStart, const glm::vec2& collBSize)
{
    glm::vec2 collAEnd = collAStart + collASize;
    glm::vec2 collBEnd = collBStart + collBSize;

    return collAStart.x < collBEnd.x &&
           collAStart.y < collBEnd.y &&
           collAEnd.x   > collBStart.x &&
           collAEnd.y   > collBStart.y;
}
