#pragma once

#include "level.hpp"
#include "floor.hpp"
#include <iostream>

class Level2 : public Level
{
    int droppable_score{};
    float camx{}, camy{};
    Floor floor{};

    virtual void loadmap() override;
    virtual void addcolliders() override;
    virtual void updatechar(float dt) override;

public:
    Level2();
    ~Level2();
    virtual bool complete() override;
};