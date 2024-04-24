#include "include/menu.hpp"

Menu::Menu()
{
    tex.load("assets/pages/menu.png");
}

Menu::~Menu()
{
    player = nullptr;
    map = nullptr;
    tex.unload();
}

void Menu::render()
{
    DrawTexture(tex.getTexture(), 0, 0, WHITE);
}
