#pragma once

#include "level.hpp"

class Level1 : public Level
{
    Sound s;
    bool first{true};

protected:
    virtual void loadmap() override;

    virtual void addcolliders() override;
    virtual void updatechar(float dt) override;

    virtual void loadinstr() override;

public:
    Level1();
    ~Level1();

    virtual void instr() override;

    virtual bool complete() override;
};
