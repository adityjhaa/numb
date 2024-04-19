#pragma once

#include "texture.hpp"
#include <vector>

class Level4
{
    std::vector<Textures> pages;
    int curr{0};
    bool done{};

public:
    Level4();
    ~Level4();

    void render();
    bool complete();
};
