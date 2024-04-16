#include "level.hpp"

class Home : public Level
{
    Textures doors[4];

    void loadmaps();
    void unloadmaps();

protected:

    virtual void loadplayer();
    virtual void addcolliders() override;
    virtual void updatechar(float dt) override;

public:
    Home();
    ~Home();
    int currmap = 0;

    virtual void render() override;
    virtual void update(float dt) override;
};
