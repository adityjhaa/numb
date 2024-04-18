#pragma once

#include "level.hpp"
#include "floor.hpp"
#include "droppable.hpp"
#include <iostream>
#define MAX_JUMP_COUNT 2
#define MAX_DROPS 4

class Level2 : public Level
{
    int droppable_score{};
    float camx{}, camy{};
    bool isIdle{false};
    int jumpCount{MAX_JUMP_COUNT - 1};
    int multiplier{};
    int dropsFrequency{};
    unsigned long long int tick{};
    unsigned long long int score{};
    Floor floor;
    Droppable drops;

    virtual void loadmap() override;
    virtual void updatechar(float dt) override;
    virtual void loadinstr() override;

public:
    Level2();
    ~Level2();
    unsigned long long int getScore();
    void loadplayer() override;
    virtual void instr() override;
    virtual bool complete() override;
};