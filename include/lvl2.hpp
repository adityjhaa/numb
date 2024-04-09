#pragma once

#include "level.hpp"

class Level2 : public Level
{
    int droppable_score{};
    float camx{}, camy{};

    virtual void loadmap() override;

    // virtual void addcolliders() override;
    virtual void updatechar(float dt) override;

public:
    Level2();
    ~Level2();
};