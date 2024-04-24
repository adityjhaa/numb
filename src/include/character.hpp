#pragma once

#include <raylib.h>
#include <raymath.h>
#include "texture.hpp"

class Character
{
protected:
    Textures idle, run, fall, jump, doubleJump, hit;

    Textures texture;
    Rectangle rec;
    Vector2 pos, vel{}, lastframe;
    float xpos{}, ypos{};
    int frame, maxframes{11};
    std::pair<bool, bool> shouldstay{};
    float speed{6.f}, scale{4.f};
    float right_left{1.f}; // right : 1.0, left : -1.0
    float updateTime, runningTime;
    float width, height;

public:
    Character();
    Character(const char *path1, const char *path2, const char *path3 = "", const char *path4 = "", const char *path5 = "", const char *path6 = "");
    ~Character();

    void initchar(Vector2 pos, int frame, float updateTime, float runningTime);

    friend class Level;
    friend class Home;
    friend class Level1;
    friend class Level2;
    friend class Level3;
    friend class Floor;
    friend class Droppable;
};
