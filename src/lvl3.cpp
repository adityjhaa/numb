#include "../include/lvl3.hpp"

Level3::Level3()
{
    loadinstr();
    loadmap();
    loadplayer();
    loadprops();
    addcolliders();
    s = LoadSound("");
}

Level3::~Level3()
{
    instpage.unload();
    unloadprops();
    player = nullptr;
    map = map1 = map2 = nullptr;
    UnloadSound(s);
}

void Level3::loadplayer()
{
    const char *path1 = "assets/main_char/Idle.png";
    const char *path2 = "assets/main_char/Run.png";
    const char *path3 = "assets/main_char/Jump.png";
    const char *path4 = "assets/main_char/Fall.png";
    const char *path5 = "assets/main_char/Double_Jump.png";
    const char *path6 = "assets/main_char/Hit.png";

    player = new Character(path1, path2, path3, path4, path5, path6);
    player->initchar(Vector2{20.f, 592.f}, 0, 1.0 / 15.0, 0.f);
}

void Level3::loadmap()
{
    map1 = new Map("assets/maps/map31.png", 4.f);
    map2 = new Map("assets/maps/map32.png", 4.f);
}

void Level3::addcolliders()
{
}

void Level3::updatechar(float dt)
{
    player->lastframe = player->pos;
    if (IsKeyDown(KEY_A))
        player->vel.x = -1.0;

    if (IsKeyDown(KEY_S) and stairs)
        player->vel.y = 1.0;

    if (IsKeyDown(KEY_D))
        player->vel.x = 1.0;

    if (IsKeyDown(KEY_W) and stairs)
        player->vel.y = -1.0;

    if (Vector2Length(player->vel) != 0.0)
    {
        player->pos = Vector2Add(player->pos, Vector2Scale(Vector2Normalize(player->vel), player->speed));

        if (player->vel.x < 0.f)
            player->right_left = -1.f;
        else if (player->vel.x > 0.f)
            player->right_left = 1.f;

        player->texture = player->run;
        player->maxframes = 12;
    }
    else
    {
        player->texture = player->idle;
        player->maxframes = 11;
    }
    player->vel = {};

    player->runningTime += dt;
    if (player->runningTime >= player->updateTime)
    {
        player->runningTime = 0.f;
        player->frame++;
        player->frame = player->frame % player->maxframes;
    }

    (player->pos.x >= 896.f and player->pos.x <= 2816.f) ? player->shouldstay.first = true : player->shouldstay.first = false;
    player->shouldstay.first ? player->xpos = 896.f : player->xpos = player->pos.x;

    player->ypos = player->pos.y;

    if (player->pos.x > 2816.f)
        player->xpos = player->pos.x - 1920;

    Rectangle source{player->frame * player->width, 0.f, player->right_left * player->width, player->height};
    Rectangle dest{player->xpos, player->ypos, player->scale * player->width, player->scale * player->height};
    if ((firstm and !enter) || (!firstm and enter))
        DrawTexturePro(player->texture.getTexture(), source, dest, Vector2{}, 0.0, WHITE);
}

void Level3::render()
{
    movecamera = player->shouldstay;
    movecamera.first ? cameramovement.first = 1 : cameramovement.first = 0;
    camx = (player->pos.x - 896.f) * cameramovement.first;

    if (!movecamera.first and (player->pos.x > 1000.f))
    {
        camx = 1920.f;
    }

    if (firstm)
    {
        map1->drawmap(Vector2{camx, camy});
        DrawTexturePro(rdoor.tex, Rectangle{(rdoor.frame % 5) * 24.f, (rdoor.frame / 5) * 24.f, 24.f, 24.f}, Rectangle{rdoor.pos.x, rdoor.pos.y, 192.f, 192.f}, Vector2{camx, camy}, 0.f, WHITE);
        for (auto t : ftorches)
            DrawTexturePro(t.tex, Rectangle{t.id * 24.f, t.frame * 24.f, 24.f, 24.f}, Rectangle{t.pos.x, t.pos.y, 96.f, 96.f}, Vector2{camx, camy}, 0.f, WHITE);
        for (auto &c : fcandles)
            DrawTexturePro(c.tex, Rectangle{c.id * 12.f, c.frame * 12.f, 12.f, 12.f}, Rectangle{c.pos.x, c.pos.y, 48.f, 48.f}, Vector2{camx, camy}, 0.f, WHITE);
        for (auto &s : fchan)
            DrawTexturePro(s.tex, Rectangle{s.id * 36.f, s.frame * 36.f, 36.f, 36.f}, Rectangle{s.pos.x, s.pos.y, 144.f, 144.f}, Vector2{camx, camy}, 0.f, WHITE);
    }
    else
    {
        map2->drawmap(Vector2{camx, camy});
        DrawTexturePro(ddoor.tex, Rectangle{(ddoor.frame % 5) * 24.f, (ddoor.frame / 5) * 24.f, 24.f, 24.f}, Rectangle{ddoor.pos.x, ddoor.pos.y, 192.f, 192.f}, Vector2{camx, camy}, 0.f, WHITE);
        for (auto &t : storches)
            DrawTexturePro(t.tex, Rectangle{t.id * 24.f, t.frame * 24.f, 24.f, 24.f}, Rectangle{t.pos.x, t.pos.y, 96.f, 96.f}, Vector2{camx, camy}, 0.f, WHITE);
        for (auto &c : scandles)
            DrawTexturePro(c.tex, Rectangle{c.id * 12.f, c.frame * 12.f, 12.f, 12.f}, Rectangle{c.pos.x, c.pos.y, 48.f, 48.f}, Vector2{camx, camy}, 0.f, WHITE);
        for (auto &s : schan)
            DrawTexturePro(s.tex, Rectangle{s.id * 36.f, s.frame * 36.f, 36.f, 36.f}, Rectangle{s.pos.x, s.pos.y, 144.f, 144.f}, Vector2{camx, camy}, 0.f, WHITE);
    }
}

void Level3::update(float dt)
{
    frame_cnt++;
    frame_cnt %= 30;

    if (IsKeyPressed(KEY_ENTER))
        opendoor = true;
    if (opendoor and (frame_cnt % 4 == 0))
        rdoor.frame++;
    if (rdoor.frame == 21)
        firstm = false;
    if (rdoor.frame > 20)
        rdoor.frame = 20;
    if ((!firstm and !dooropen) and (frame_cnt % 4 == 0))
        ddoor.frame++;
    if (ddoor.frame == 20)
        enter = true;
    if (ddoor.frame > 20)
        ddoor.frame = 20;

    if (frame_cnt % 10 == 0)
    {
        for (auto &t : ftorches)
        {
            t.frame++;
            t.frame %= 3;
        }
        for (auto &t : storches)
        {
            t.frame++;
            t.frame %= 3;
        }
    }

    if (frame_cnt % 5 == 0)
    {
        for (auto &c : fcandles)
        {
            c.frame++;
            c.frame %= 6;
        }
        for (auto &c : scandles)
        {
            c.frame++;
            c.frame %= 6;
        }
        for (auto &s : fchan)
        {
            s.frame++;
            s.frame %= 6;
        }
        for (auto &s : schan)
        {
            s.frame++;
            s.frame %= 6;
        }
    }

    updatechar(dt);
}

bool Level3::complete()
{
    return false;
}

void Level3::loadinstr()
{
    instpage.load("assets/pages/instr3.png");
}

void Level3::instr()
{
    DrawTexture(instpage.getTexture(), 0, 0, WHITE);
}

void Level3::loadprops()
{
    ftorches.push_back(Torch{0, 0, Vector2{312.f, 336.f}});
    ftorches.push_back(Torch{1, 0, Vector2{456.f, 336.f}});
    ftorches.push_back(Torch{4, 0, Vector2{1272.f, 336.f}});
    ftorches.push_back(Torch{5, 0, Vector2{1416.f, 336.f}});
    ftorches.push_back(Torch{8, 0, Vector2{2232.f, 336.f}});
    ftorches.push_back(Torch{9, 0, Vector2{2376.f, 336.f}});
    ftorches.push_back(Torch{12, 0, Vector2{3192.f, 336.f}});
    ftorches.push_back(Torch{13, 0, Vector2{3336.f, 336.f}});

    storches.push_back(Torch{2, 0, Vector2{312.f, 336.f}});
    storches.push_back(Torch{3, 0, Vector2{456.f, 336.f}});
    storches.push_back(Torch{6, 0, Vector2{1272.f, 336.f}});
    storches.push_back(Torch{7, 0, Vector2{1416.f, 336.f}});
    storches.push_back(Torch{10, 0, Vector2{2232.f, 336.f}});
    storches.push_back(Torch{11, 0, Vector2{2376.f, 336.f}});
    storches.push_back(Torch{14, 0, Vector2{3192.f, 336.f}});
    storches.push_back(Torch{15, 0, Vector2{3336.f, 336.f}});

    fcandles.push_back(Candles{0, 0, Vector2{3552.f, 336.f}});
    fcandles.push_back(Candles{1, 0, Vector2{3696.f, 336.f}});
    scandles.push_back(Candles{2, 0, Vector2{3552.f, 336.f}});
    scandles.push_back(Candles{3, 0, Vector2{3696.f, 336.f}});

    fchan.push_back(Chandelier{0, 0, Vector2{648.f, 0.f}});
    fchan.push_back(Chandelier{1, 0, Vector2{1608.f, 0.f}});
    fchan.push_back(Chandelier{0, 0, Vector2{2568.f, 0.f}});
    fchan.push_back(Chandelier{1, 0, Vector2{3528.f, 0.f}});
    schan.push_back(Chandelier{2, 0, Vector2{648.f, 0.f}});
    schan.push_back(Chandelier{3, 0, Vector2{1608.f, 0.f}});
    schan.push_back(Chandelier{2, 0, Vector2{2568.f, 0.f}});
    schan.push_back(Chandelier{3, 0, Vector2{3528.f, 0.f}});

    
}

void Level3::unloadprops()
{
    for (auto &t : ftorches)
        UnloadTexture(t.tex);
    for (auto &t : storches)
        UnloadTexture(t.tex);

    for (auto &c : fcandles)
        UnloadTexture(c.tex);
    for (auto &c : scandles)
        UnloadTexture(c.tex);

    for (auto &s : fchan)
        UnloadTexture(s.tex);
    for (auto &s : schan)
        UnloadTexture(s.tex);
}