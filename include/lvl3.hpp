#pragma once

#include "level.hpp"
#include "enemy.hpp"

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

class Level3 : public Level
{
    Map *map1, *map2;
    std::vector<std::pair<Enemy *, bool>> enemies;
    Sound s;
    Textures instpage2;
    Textures heal;

    int frame_cnt{}, fall_frame{}, frame3{}, jumpCount{0}, stairs{}, health{3}, hitcnt{};
    bool firstm{true}, opendoor{}, dooropen{}, enter{}, jump{}, phit{}, ehit{}, lose{}, instr2{};

    std::vector<Torch> ftorches;
    std::vector<Torch> storches;

    std::vector<Candles> fcandles;
    std::vector<Candles> scandles;

    std::vector<Chandelier> fchan;
    std::vector<Chandelier> schan;

    std::vector<Water> water;
    std::vector<Lava> lava;
    std::vector<WaterFall> waterf;
    std::vector<LavaFall> lavaf;

    RDoor rdoor;
    DDoor ddoor;
    Fountain fountain;

    Rectangle antimatter{2832.f, 720.f, 192.f, 288.f};

    bool fall();
    void playerhit();
    void enemyhit();

protected:
    virtual void loadmap() override;
    virtual void loadplayer() override;

    virtual void addcolliders() override;
    virtual void updatechar(float dt) override;
    virtual void loadinstr() override;

    void loadprops();
    void loadenemies();
    void unloadprops();

    void updateenemies(float dt);

public:
    Level3();
    ~Level3();

    virtual void instr() override;

    virtual void render() override;
    virtual void update(float dt) override;

    virtual bool complete() override;
    bool incomplete();
};
