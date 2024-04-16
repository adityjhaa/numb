#include "../include/home.hpp"

Home::Home()
{
    loadplayer();
    loadmaps();
}

Home::~Home()
{
    player = nullptr;
    map = nullptr;
    unloadmaps();
}

void Home::loadmaps()
{
    doors[0].load("assets/maps/mdr/map01.png");
    doors[1].load("assets/maps/mdr/map03.png");
    doors[2].load("assets/maps/mdr/map03.png");
    doors[3].load("assets/maps/mdr/map04.png");
}

void Home::unloadmaps()
{
    for(auto d : doors)
    {
        d.unload();
    }
}

void Home::updatechar(float dt)
{
}

void Home::render()
{
    DrawTexture(doors[currmap].getTexture(), 0, 0, WHITE);
}

void Home::update(float dt)
{

}
