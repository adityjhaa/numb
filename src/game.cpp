#include "../include/game.hpp"

Game::Game() {}

Game::~Game() {m=nullptr;}

void Game::initwindow(int width, int height, const char *title)
{
    InitWindow(width, height, title);
    m = new Character();
    addCharacter();
}

void Game::startscreen(const char *name){
    bool startplay{false};
    while((!startplay) && (!WindowShouldClose())){
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText(name,780,460,80,YELLOW);
        
        DrawText("<SPACE> to PLAY",775,800,40,RED);
        if(IsKeyPressed(KEY_SPACE)){startplay=true;}
        EndDrawing();
    }
}

void Game::addCharacter()
{
    m->loadTexture("assets/main_char/Idle.png");
    m->make(Vector2{0.f, 0.f}, 0, 11, 1.0 / 12.0, 0.0);
}

void Game::draw(float dt)
{
    m->runningTime += dt;
    if (m->runningTime >= m->updateTime)
    {
        m->runningTime = 0.0;
        m->rec.x = m->frame * m->rec.width;
        m->frame++;
        m->frame = m->frame % m->noframes;
    }
    Rectangle dest = {100.0, 100.0, m->rec.width*8, m->rec.height*8};
    DrawTexturePro(m->tex, m->rec, dest, m->pos, 0.0, WHITE);
}

void Game::render(float dt)
{
    BeginDrawing();
    ClearBackground(WHITE);

    Game::draw(dt);

    EndDrawing();
}