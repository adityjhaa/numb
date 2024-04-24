#pragma once

#include <raylib.h>
#include <raymath.h>
#include "texture.hpp"

class Enemy
{
protected:
    Textures idle, run, hit;
    Textures texture;

    Rectangle rec;
    Vector2 pos, vel{}, lastframe;
    int start, end;

    int frame, maxframes{11};
    float width, height;
    float xpos{}, ypos{}, speed{3.f}, scale{3.f};
    float right_left{1.f}; // right : 1.0, left : -1.0
    float updateTime, runningTime;

public:
    Enemy();
    Enemy(const char *path1, const char *path2, const char *path3);
    ~Enemy();

    void initenemy(Vector2 pos, int start, int end);

    bool followplayer(Vector2 playerpos);

    friend class Level3;
};
