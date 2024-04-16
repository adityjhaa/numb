#pragma once

#include <raylib.h>
#include <raymath.h>
#include <vector>
#include <iostream>
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
    void draw();
    void CheckCollision();
    ~Floor();
};