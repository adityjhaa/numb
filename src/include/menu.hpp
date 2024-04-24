#include "level.hpp"

class Menu : public Level
{
    Textures tex;

protected:
public:
    Menu();
    ~Menu();

    virtual void render() override;
};
