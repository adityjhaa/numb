#pragma once

#include "level.hpp"
#include "enemy.hpp"
#include "decoration.hpp"

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
