#include "../include/game.hpp"

std::pair<bool, int> collisionx(Rectangle rec1, Rectangle rec2)
{
    if ((rec1.y + rec1.height > rec2.y) and (rec1.y < rec2.y + rec2.height))
    {
        if ((rec1.x + rec1.width > rec2.x) and (rec1.x < rec2.x))
        {
            return {true, 1};
        }
        if ((rec2.x + rec2.width > rec1.x) and (rec2.x < rec1.x))
        {
            return {true, -1};
        }
    }

    return {false, 0};
}

std::pair<bool, int> collisiony(Rectangle rec1, Rectangle rec2)
{
    if ((rec1.x + rec1.width > rec2.x) and (rec1.x < rec2.x + rec2.width))
    {
        if ((rec1.y + rec1.height > rec2.y) and (rec1.y < rec2.y))
        {
            return {true, 1};
        }
        if ((rec2.y + rec2.height > rec1.y) and (rec2.y < rec1.y))
        {
            return {true, -1};
        }
    }

    return {false, 0};
}
