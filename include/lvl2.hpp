#pragma once

#include "level.hpp"
#include "floor.hpp"
#include <iostream>
#define MAX_JUMP_COUNT 2

class Level2 : public Level
{
    int droppable_score{};
    float camx{}, camy{};
    bool isIdle{false};
    int jumpCount{MAX_JUMP_COUNT-1};
    Floor floor{};

    virtual void loadmap() override;
    virtual void addcolliders() override;
    virtual void updatechar(float dt) override;
    virtual void loadplayer() override;

public:
    Level2();
    ~Level2();
    virtual bool complete() override;
};