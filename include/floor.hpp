#pragma once

#include <raylib.h>
#include <raymath.h>
#include <vector>
#include <iostream>
#include "character.hpp"
#include "texture.hpp"

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
    Floor(char* path);
    void Draw(Character* player, float camx, float camy);
    bool CheckCollision(Character* player);
    ~Floor();
};