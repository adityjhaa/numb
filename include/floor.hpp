#pragma once

#include "character.hpp"
#include <vector>

struct Block
{
    Textures texture;
    Rectangle rect;
    bool is_active;
};

class Floor
{
    std::vector<std::vector<Block>> floor;

public:
    Floor();
    Floor(char *path);
    void Draw(Character *player, float camx, float camy);
    bool CheckCollision(Character *player, float playerx, float playery);
    std::vector<std::vector<Block>> getFloor();
    void removeBlock(int i, int j);
    ~Floor();
};