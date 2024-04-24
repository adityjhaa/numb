#include "include/lvl3.hpp"
#include <iostream>

Level3::Level3()
{
    loadinstr();
    loadmap();
    loadplayer();
    loadenemies();
    loadprops();
    addcolliders();
    s = LoadSound("");
}

Level3::~Level3()
{
    instpage.unload();
    instpage2.unload();
    unloadprops();
    delete player;
    player = nullptr;
    delete map1;
    delete map2;
    map = map1 = map2 = nullptr;
    UnloadSound(s);
    for (auto e : enemies)
    {
        delete e.first;
        e.first = nullptr;
    }
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
    heal.load("assets/drops/health.png");
}

void Level3::addcolliders()
{
    colliders.push_back(Rectangle{1680.f, 240.f, 96.f, 144.f});
}

void Level3::updatechar(float dt)
{
    if ((player->pos.x > 3352.f) and (player->pos.x < 3386.f))
    {
        if (player->pos.y >= 592.f)
            stairs = 1; // can go up
        if (player->pos.y <= 252.f)
            stairs = 2; // can go down
        if ((player->pos.y < 592.f) and (player->pos.y > 252.f))
            stairs = 3; // both
    }

    bool f = fall();

    if (f)
        jumpCount = 5;

    player->lastframe = player->pos;
    if (IsKeyDown(KEY_A))
        player->vel.x -= 1.0;

    if (IsKeyDown(KEY_D))
        player->vel.x += 1.0;

    if (IsKeyDown(KEY_W) and (stairs % 2))
        player->vel.y = -1.0;

    if (IsKeyPressed(KEY_SPACE) and jumpCount < 2)
    {
        player->vel.y = -1.f;
        jumpCount++;
    }

    if (f)
    {
        player->vel.y = 0.8;
        player->vel.x = 0.f;
    }

    player->pos = Vector2Add(player->pos, Vector2Scale(Vector2Normalize(player->vel), player->speed));

    if (Vector2Length(player->vel) != 0.0)
    {

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

    jump = false;

    if (player->vel.y < 0.f)
    {
        if (jumpCount == 1)
        {
            jump = true;
            player->texture = player->jump;
            player->maxframes = 1;
        }
        else if (jumpCount == 2)
        {
            jump = true;
            player->texture = player->doubleJump;
            player->maxframes = 6;
        }
    }

    if ((player->vel.y > 0.f) || f)
    {
        jump = true;
        player->texture = player->fall;
        player->maxframes = 1;
    }

    player->vel.x = {};

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

    if ((player->pos.y >= 256.f) and (player->pos.y <= 260.f) and (player->pos.x > 3392.f))
    {
        player->vel.y = 0.f;
        jumpCount = 0;
    }
    else if (player->pos.y < 592.f)
    {
        player->vel.y += 0.05;
    }
    else
    {
        player->vel.y = 0.f;
        jumpCount = 0;
    }

    if ((player->pos.x <= -64.f) || player->pos.x >= 3776.f)
    {
        player->pos = player->lastframe;
    }

    if (player->pos.x > 2816.f)
        player->xpos = player->pos.x - 1920;

    if (player->pos.y > 1200.f)
        player->pos.y = 1200.f;

    stairs = 0;

    if (!ehit)
        playerhit();

    if (phit)
    {
        player->texture = player->hit;
        player->maxframes = 7;
        hitcnt++;
    }
    else
        phit = false;

    if (hitcnt == 105)
    {
        phit = false;
        hitcnt = 0;
    }

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
            DrawTexturePro(t.tex, Rectangle{t.id * 24.f, frame3 * 24.f, 24.f, 24.f}, Rectangle{t.pos.x, t.pos.y, 96.f, 96.f}, Vector2{camx, camy}, 0.f, WHITE);
        for (auto &c : fcandles)
            DrawTexturePro(c.tex, Rectangle{c.id * 12.f, c.frame * 12.f, 12.f, 12.f}, Rectangle{c.pos.x, c.pos.y, 48.f, 48.f}, Vector2{camx, camy}, 0.f, WHITE);
        for (auto &s : fchan)
            DrawTexturePro(s.tex, Rectangle{s.id * 36.f, s.frame * 36.f, 36.f, 36.f}, Rectangle{s.pos.x, s.pos.y, 144.f, 144.f}, Vector2{camx, camy}, 0.f, WHITE);
        for (auto &l : lavaf)
            DrawTexturePro(l.tex, Rectangle{(fall_frame % 5) * 24.f, (fall_frame / 5) * 48.f}, Rectangle{l.pos.x, l.pos.y, 48.f, 48.f}, Vector2{camx, camy}, 0.f, WHITE);
    }
    else
    {
        map2->drawmap(Vector2{camx, camy});
        DrawTexturePro(ddoor.tex, Rectangle{(ddoor.frame % 5) * 24.f, (ddoor.frame / 5) * 24.f, 24.f, 24.f}, Rectangle{ddoor.pos.x, ddoor.pos.y, 192.f, 192.f}, Vector2{camx, camy}, 0.f, WHITE);
        for (auto &t : storches)
            DrawTexturePro(t.tex, Rectangle{t.id * 24.f, frame3 * 24.f, 24.f, 24.f}, Rectangle{t.pos.x, t.pos.y, 96.f, 96.f}, Vector2{camx, camy}, 0.f, WHITE);
        for (auto &c : scandles)
            DrawTexturePro(c.tex, Rectangle{c.id * 12.f, c.frame * 12.f, 12.f, 12.f}, Rectangle{c.pos.x, c.pos.y, 48.f, 48.f}, Vector2{camx, camy}, 0.f, WHITE);
        for (auto &s : schan)
            DrawTexturePro(s.tex, Rectangle{s.id * 36.f, s.frame * 36.f, 36.f, 36.f}, Rectangle{s.pos.x, s.pos.y, 144.f, 144.f}, Vector2{camx, camy}, 0.f, WHITE);
        for (auto &l : waterf)
            DrawTexturePro(l.tex, Rectangle{(fall_frame % 5) * 24.f, (fall_frame / 5) * 48.f}, Rectangle{l.pos.x, l.pos.y, 48.f, 48.f}, Vector2{camx, camy}, 0.f, WHITE);

        DrawTexturePro(fountain.tex, Rectangle{(frame3 % 2) * 24.f, (frame3 / 2) * 24.f, 24.f, 24.f}, Rectangle{fountain.pos.x, fountain.pos.y, 144.f, 144.f}, Vector2{camx, camy}, 0.f, WHITE);
    }

    for (int i = 0; i < health; i++)
        DrawTexture(heal.getTexture(), 20.f + i * 120.f, 20.f, WHITE);
}

void Level3::update(float dt)
{
    frame_cnt++;
    frame_cnt %= 30;

    player->rec = Rectangle{player->pos.x + 20.f - camx, player->pos.y + 20.f, 88.f, 108.f};

    {
        if (IsKeyPressed(KEY_S) and CheckCollisionRecs(player->rec, colliders[0]) and firstm)
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
    }

    if (frame_cnt % 8 == 0)
    {
        frame3++;
        frame3 %= 3;
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

    if (frame_cnt % 3 == 0)
    {
        fall_frame++;
        fall_frame %= 9;
    }

    if (!lose)
    {
        updateenemies(dt);
        updatechar(dt);
    }

    if (firstm)
    {
        for (auto &l : lava)
            DrawTexturePro(l.tex, Rectangle{(fall_frame % 5) * 24.f, 6.f + (fall_frame / 5) * 72.f, 24.f, 36.f}, Rectangle{l.pos.x, l.pos.y, 144.f, 144.f}, Vector2{camx, camy}, 0.f, WHITE);
    }
    else
    {
        for (auto &l : water)
            DrawTexturePro(l.tex, Rectangle{(fall_frame % 5) * 24.f, 6.f + (fall_frame / 5) * 72.f, 24.f, 36.f}, Rectangle{l.pos.x, l.pos.y, 144.f, 144.f}, Vector2{camx, camy}, 0.f, WHITE);
    }
}

bool Level3::complete()
{
    if (!firstm and player->pos.x <= 100.f)
        finish = true;

    return finish and IsKeyPressed(KEY_ENTER);
}

void Level3::loadinstr()
{
    instpage.load("assets/pages/instr31.png");
    instpage2.load("assets/pages/instr32.png");
}

void Level3::instr()
{
    if (IsKeyPressed(KEY_RIGHT))
        instr2 = true;

    if (!instr2)
        DrawTexture(instpage.getTexture(), 0, 0, WHITE);
    else
        DrawTexture(instpage2.getTexture(), 0, 0, WHITE);
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

    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 21; ++j)
        {
            lavaf.push_back(LavaFall{Vector2{2880.f + i * 48.f, j * 48.f}});
            waterf.push_back(WaterFall{Vector2{2880.f + i * 48.f, j * 48.f}});
        }
    }

    for (int i = 0; i < 40; ++i)
    {
        lava.push_back(Lava{Vector2{i * 96.f, 960.f}});
        water.push_back(Water{Vector2{i * 96.f, 960.f}});
    }
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

    for (auto &l : water)
        UnloadTexture(l.tex);
    for (auto &l : waterf)
        UnloadTexture(l.tex);
    for (auto &l : lava)
        UnloadTexture(l.tex);
    for (auto &l : lavaf)
        UnloadTexture(l.tex);

    UnloadTexture(rdoor.tex);
    UnloadTexture(ddoor.tex);
    UnloadTexture(fountain.tex);
}

bool Level3::fall()
{
    if (player->pos.y >= 592.f)
    {
        if ((player->pos.x > antimatter.x - 32.f) and (player->pos.x < (antimatter.x + antimatter.width - 92.f)))
        {
            return true;
        }
    }
    return false;
}

void Level3::loadenemies()
{
    for (int i = 0; i < 5; i++)
        enemies.push_back({new Enemy("assets/enemy/Idle.png", "assets/enemy/Run.png", "assets/enemy/Hit.png"), (i % 2 != 0)});

    enemies[0].first->initenemy(Vector2{632.f, 576.f}, 248, 1028);
    enemies[1].first->initenemy(Vector2{1592.f, 576.f}, 1212, 1992);
    enemies[2].first->initenemy(Vector2{1592.f, 576.f}, 1212, 1992);
    enemies[3].first->initenemy(Vector2{2480, 576.f}, 2172, 2700);
    enemies[4].first->initenemy(Vector2{2480, 576.f}, 2172, 2700);
}

void Level3::updateenemies(float dt)
{
    if (!phit)
        enemyhit();

    for (auto e : enemies)
    {
        if (e.second != firstm)
            continue;

        if (e.first->followplayer(player->pos))
        {
            e.first->vel = Vector2Scale(Vector2Normalize(Vector2{e.first->pos.x - player->pos.x, 0.f}), e.first->speed);
            if (e.first->pos.x <= e.first->start or e.first->pos.x >= e.first->end)
                e.first->vel = {};
            e.first->pos = Vector2Subtract(e.first->pos, e.first->vel);
        }
        if (Vector2Length(e.first->vel) != 0.f)
        {
            if (e.first->vel.x > 0.f)
                e.first->right_left = 1;
            else if (e.first->vel.x < 0.f)
                e.first->right_left = -1;

            e.first->texture = e.first->run;
            e.first->maxframes = 12;
        }
        else
        {
            e.first->texture = e.first->idle;
            e.first->maxframes = 11;
        }

        e.first->runningTime += dt;
        if (e.first->runningTime >= e.first->updateTime)
        {
            e.first->runningTime = 0.f;
            e.first->frame++;
            e.first->frame = e.first->frame % e.first->maxframes;
        }
        e.first->vel = {};

        if (ehit)
        {
            e.first->texture = e.first->hit;
            e.first->maxframes = 7;
            hitcnt++;
        }
        else
            ehit = false;

        if (hitcnt == 105)
        {
            ehit = false;
            hitcnt = 0;
        }

        e.first->rec = Rectangle{e.first->pos.x - camx + 39.f, e.first->pos.y + 75.f, 66.f, 69.f};

        DrawTexturePro(e.first->texture.getTexture(), Rectangle{e.first->frame * e.first->width, 0.f, e.first->right_left * e.first->width, e.first->height}, Rectangle{e.first->pos.x, e.first->pos.y, e.first->width * e.first->scale, e.first->height * e.first->scale}, Vector2{camx, camy}, 0.f, WHITE);
    }
}

bool Level3::incomplete()
{
    if (player->pos.y > 1180.f)
    {
        lose = true;
    }

    if (health == 0)
    {
        lose = true;
    }

    return lose and IsKeyPressed(KEY_ENTER);
}

void Level3::playerhit()
{
    for (auto e : enemies)
    {
        if (!jump and CheckCollisionRecs(player->rec, e.first->rec) and !phit)
        {
            phit = true;
            health--;
        }
    }
}

void Level3::enemyhit()
{
    for (auto e : enemies)
    {
        if (jump and CheckCollisionRecs(player->rec, e.first->rec) and !ehit)
            ehit = true;
    }
}
