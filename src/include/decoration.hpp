#pragma once

#include <raylib.h>

struct RDoor
{
    int frame = 0;
    Vector2 pos = {3552.f, 192.f};
    Texture2D tex = LoadTexture("assets/props/RDoor.png");
};

struct DDoor
{
    int frame = 0;
    Vector2 pos = {3552.f, 192.f};
    Texture2D tex = LoadTexture("assets/props/DDoor.png");
};

struct Water
{
    Vector2 pos;
    Texture2D tex = LoadTexture("assets/props/FlowingWater.png");
};

struct Lava
{
    Vector2 pos;
    Texture2D tex = LoadTexture("assets/props/FlowingLava.png");
};

struct WaterFall
{
    Vector2 pos;
    Texture2D tex = LoadTexture("assets/props/FallingWater.png");
};

struct LavaFall
{
    Vector2 pos;
    Texture2D tex = LoadTexture("assets/props/FallingLava.png");
};

struct Torch
{
    int id;
    int frame;
    Vector2 pos;
    Texture2D tex = LoadTexture("assets/props/Torches.png");
};

struct Candles
{
    int id;
    int frame;
    Vector2 pos;
    Texture2D tex = LoadTexture("assets/props/Candles.png");
};

struct Chandelier
{
    int id;
    int frame;
    Vector2 pos;
    Texture2D tex = LoadTexture("assets/props/Chandeliers.png");
};

struct Fountain
{
    int frame{};
    Vector2 pos{5.f, 576.f};
    Texture tex = LoadTexture("assets/props/Fountain.png");
};
