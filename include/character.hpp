#pragma once

#include "raylib.h"

class Character
{

public:
    Texture2D tex;
    Rectangle rec;
    Vector2 pos;
    int frame;
    int noframes;
    float updateTime, runningTime;
    Character();

    ~Character();

    void loadTexture(const char *path);

    void make(Vector2 pos, int frame, int noframes, float updateTime, float runningTime);

    void unloadTexture();
};
