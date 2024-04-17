#pragma once

#include "level.hpp"
#include "floor.hpp"
#include "droppable.hpp"
#include <iostream>
#define MAX_JUMP_COUNT 2
#define DROPS_FREQUENCY 120
#define DIFFICULTY_FACTOR 1000

class Level2 : public Level
{
    int droppable_score{};
    float camx{}, camy{};
    bool isIdle{false};
    int jumpCount{MAX_JUMP_COUNT-1};
    unsigned long long int tick{};
    Floor floor;
    Droppable drops;

    virtual void loadmap() override;
    virtual void addcolliders() override;
    virtual void updatechar(float dt) override;

public:
    Level2();
    ~Level2();
    void loadplayer() override;
    virtual bool complete() override;
};