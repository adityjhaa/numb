#pragma once

#include "level.hpp"

class Level1 : public Level
{
protected:
    virtual void loadmap() override;

    virtual void addcolliders() override;
    virtual void updatechar(float dt) override;
public:
    Level1();
    ~Level1();
};