#include "level.hpp"

class Home : public Level
{
    Textures doors[4];

    void loadmaps();
    void unloadmaps();

    void entries();

protected:
    virtual void loadplayer();
    virtual void updatechar(float dt) override;

public:
    Home();
    ~Home();
    int currmap = 0;
    int pressed = 0;
    virtual void render() override;
    virtual void update(float dt) override;
};
