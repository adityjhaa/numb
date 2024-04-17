#pragma once

#include "level.hpp"

class Level3 : public Level
{
    Map *map1, *map2;
    Sound s;
    bool first{true};

protected:
    virtual void loadmap() override;
    virtual void loadplayer() override;

    virtual void addcolliders() override;
    virtual void updatechar(float dt) override;
    virtual void loadinstr() override;

public:
    Level3();
    ~Level3();

    virtual void instr() override;

    virtual void render() override;
    virtual void update(float dt) override;

    virtual bool complete() override;
};
