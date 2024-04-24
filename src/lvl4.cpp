#include "include/lvl4.hpp"

Level4::Level4()
{
    pages.push_back(Textures{});
    pages.push_back(Textures{});
    pages.push_back(Textures{});

    pages[0].load("assets/pages/41.png");
    pages[1].load("assets/pages/42.png");
    pages[2].load("assets/pages/43.png");
}

Level4::~Level4()
{
    pages[0].unload();
    pages[1].unload();
    pages[2].unload();
}

void Level4::render()
{
    DrawTexture(pages[curr].getTexture(), 0, 0, WHITE);
    if (IsKeyPressed(KEY_RIGHT) and curr != 2)
        curr++;

    if (IsKeyPressed(KEY_SPACE) and curr == 2)
        done = true;
}

bool Level4::complete()
{
    return done;
}
