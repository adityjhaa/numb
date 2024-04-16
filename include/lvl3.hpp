#pragma once

#include "level.hpp"

class Level3 : public Level
{
    Sound s;
    bool first{true};

protected:
    virtual void loadmap() override;

    virtual void addcolliders() override;
    virtual void updatechar(float dt) override;

public:
    Level3();
    ~Level3();
    virtual bool complete() override;
};
