#include "Game.h"


Game::Game()
{
    isInitialized = false;
}

int Game::run(sf::RenderWindow &window)
{
    Event event;

    Clock clock;

    Texture texDynamicObjects;
    texDynamicObjects.loadFromFile("images/DynamicObjects.png");
    Texture texMap;
    texMap.loadFromFile("images/grass.png");
    Texture texMapObjects;
    texMapObjects.loadFromFile("images/MapObjects.png");
    Texture texGUI;
    texGUI.loadFromFile("images/GUI.png");

    std::list<Enemy*> enemies;
    std::list<Enemy*>::iterator it_enemies;

    std::list<Bullet*> bullets;
    std::list<Bullet*>::iterator it_bullets;

    std::list<GameObject*> objects;
    std::list<GameObject*>::iterator it_static_objects;

    std::list<Animation*> anims;
    std::list<Animation*>::iterator it_anims;

    Map map(texMap, texMapObjects, objects, 0);

    Player player(Vector2f(200, 200), germanyPz1C);

    Crosshair crosshair(Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), texGUI, IntRect(0, 0, 24, 24));

    level = 0;

    //enemies.push_back(new Enemy(Vector2f(0, 100), &texDynamicObjects, GERMANY_TIGER2));
    //enemies.push_back(new Enemy(Vector2f(2000, 1500), &texDynamicObjects, GERMANY_TIGER2));

    Vector2u windowSize;
    view.reset(FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));

    /* direction - задаёт направление движения танка игрока:
    Принимает значение 1, если нажата кнопка W
    и -1, если нажата S */
    short int direction = 0;
    /* rotation - задаёт направление поворота танка игрока:
    Принимает значение 1, если нажата кнопка D
    и -1, если нажата A */
    short int rotation = 0;

    bool running = true;

    while (running) {
        // Проверяем если нет врагов, то добавляем новых
        if (enemies.empty()) {
            level++;

            createEnemies(enemies, texDynamicObjects, level);
        }

        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                return -1;
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            // Создаём экран "Меню паузы"
            std::vector<MenuPoint> menuPoints;
            MenuPoint point;

            point.text.setString(L"Продолжить");
            point.value = 1;
            menuPoints.push_back(point);
            point.text.setString(L"Выход");
            point.value = -1;
            menuPoints.push_back(point);

            MenuPause pauseMenu;
            switch (pauseMenu.run(window)) {
                case 1:
                    continue;
                    break;
                case 0:
                    return 0;
                    break;
                case -1:
                    return -1;
                    break;
            }

        }

        direction = 0;
        rotation = 0;

        if (Keyboard::isKeyPressed(Keyboard::D)) {
            rotation = 1;
        }
        if (Keyboard::isKeyPressed(Keyboard::A)) {
            rotation = -1;
        }
        if (Keyboard::isKeyPressed(Keyboard::W)) {
            direction = 1;
        }
        if (Keyboard::isKeyPressed(Keyboard::S)) {
            direction = -1;
        }
        if (event.type == Event::MouseButtonPressed &&
            event.key.code == Mouse::Left) {
            player.fire(bullets, texDynamicObjects);
        }

        // Зум. Работает косячно.
        /*if (event.type == Event::MouseWheelMoved) {
            Vector2f backupView = view.getSize();
            std::cout << backupView.x << "  " << backupView.y << std::endl;
            FloatRect newView;
            newView.left = 0;
            newView.top = 0;

            if (event.mouseWheel.delta < 0) {
                if (backupView.x < 1920 && backupView.y < 1080) {
                    newView.width = backupView.x * 1.1;
                    newView.height = backupView.y * 1.1;
                    view.reset(newView);
                }
            }
            if (event.mouseWheel.delta > 0) {
                if (backupView.x > 960 && backupView.y > 540) {
                    newView.width = backupView.x / 1.1;
                    newView.height = backupView.y / 1.1;
                    view.reset(newView);
                }
            }
            event.mouseWheel.delta = 0;
        }*/


        double time = (double)clock.getElapsedTime().asMicroseconds();
        time = time / 1000;
        clock.restart();

        view = getViewCoords(player.getPos().x, player.getPos().y);

        for (it_bullets = bullets.begin(); it_bullets != bullets.end();) {
            Bullet* b = *it_bullets;

            if (b->isAlive() == false) {
                it_bullets = bullets.erase(it_bullets);
                delete b;
            } else {
                it_bullets++;
            }
        }

        for (it_anims = anims.begin(); it_anims != anims.end();) {
            Animation *a = *it_anims;

            if ((*it_anims)->isAlive() == false) {
                it_anims = anims.erase(it_anims);
                delete a;
            } else {
                it_anims++;
            }
        }

        for (it_enemies = enemies.begin(); it_enemies != enemies.end();) {
            Enemy *e = *it_enemies;

            if ((*it_enemies)->isAlive() == false) {
                it_enemies = enemies.erase(it_enemies);
                delete e;
            } else {
                it_enemies++;
            }
        }

        windowSize = window.getSize();
        Vector2i mousePos = getMouseCoords(Mouse::getPosition(window), windowSize);
        player.update(time, direction, rotation, objects, enemies, bullets, anims);
        player.rotateTurrel(mousePos);

        window.setView(view);
        window.clear();

        map.draw(window, objects);
        player.draw(window);
        for (it_enemies = enemies.begin(); it_enemies != enemies.end(); it_enemies++) {
            Tank playerTank = player;
            (*it_enemies)->update(time, playerTank, bullets, objects, anims, enemies);
            (*it_enemies)->draw(window);
            // window.draw((*it_enemies)->bigSprite); // Потом удалить
        }

        for (it_bullets = bullets.begin(); it_bullets != bullets.end(); it_bullets++) {
            (*it_bullets)->update(time, view, window, objects, anims);
            (*it_bullets)->draw(window);
        }

        for (it_anims = anims.begin(); it_anims != anims.end(); it_anims++) {
            (*it_anims)->update(time);
            (*it_anims)->draw(window);
        }



        crosshair.update((Vector2f)mousePos, enemies, player);
        crosshair.draw(window);

        window.display();
    }
    return 0;
}

RespawnInfo Game::getRespawnInfo(int randomizer)
{
    srand(randomizer);
    int corn = rand() % 8;
    RespawnInfo inf;

    switch (corn) {
        case 0:
            inf.spawnPos = Vector2f(0, 100);
            inf.spawnRotation = 0;
            break;
        case 1:
            inf.spawnPos = Vector2f(100, 0);
            inf.spawnRotation = 90;
            break;
        case 2:
            inf.spawnPos = Vector2f(mapWidth, 100);
            inf.spawnRotation = 180;
            break;
        case 3:
            inf.spawnPos = Vector2f(mapWidth - 100, 0);
            inf.spawnRotation = 90;
            break;
        case 4:
            inf.spawnPos = Vector2f(0, mapHeight - 100);
            inf.spawnRotation = 0;
            break;
        case 5:
            inf.spawnPos = Vector2f(100, mapHeight);
            inf.spawnRotation = -90;
            break;
        case 6:
            inf.spawnPos = Vector2f(mapWidth, mapHeight - 100);
            inf.spawnRotation = 180;
            break;
        case 7:
            inf.spawnPos = Vector2f(mapWidth - 100, mapHeight);
            inf.spawnRotation = -90;
            break;
    }
    inf.corn = corn;
    return inf;
}

bool Game::isTheSameCorn(int a, int b)
{
    if (((a == 0) && (b == 1)) || ((a == 1) && (b == 0)) ||
        ((a == 2) && (b == 3)) || ((a == 3) && (b == 2)) ||
        ((a == 4) && (b == 5)) || ((a == 5) && (b == 4)) ||
        ((a == 6) && (b == 7)) || ((a == 7) && (b == 6))) {
        return true;
    } else {
        return false;
    }
}

void Game::createEnemies(std::list<Enemy*> &enemies, Texture &texDynObjs, int lvl)
{
    int count;
    double multiplier;

    RespawnInfo respInfo;
    std::vector<int> prevCorns;

    TankCharacteristic *newEnemy;

    if (lvl <= 5) {
        newEnemy = &germanyTiger2;
    } else if (lvl <= 10) {
        newEnemy = &germanyTiger2;
    } else if (lvl <= 15) {
        newEnemy = &germanyTiger2;
    } else if (lvl <= 20) {
        newEnemy = &germanyTiger2;
    } else if (lvl <= 25) {
        newEnemy = &germanyTiger2;
    }

    switch (lvl % 5) {
        case 1:
            count = 1;
            multiplier = 1;
            break;
        case 2:
            count = 2;
            multiplier = 1;
            break;
        case 3:
            count = 2;
            multiplier = 1.5;
            break;
        case 4:
            count = 3;
            multiplier = 1.5;
            break;
        case 0:
            count = 3;
            multiplier = 2;
            break;
    }

    for (int i = 0; i < count; ++i) {
        bool isTheSame = true;
        while (isTheSame) {
            respInfo = getRespawnInfo(lvl * 100);
            for (std::vector<int>::iterator it = prevCorns.begin();
                it != prevCorns.end(); it++) {
                if (*it == respInfo.corn) {
                    isTheSame = true;
                    break;
                } else {
                    isTheSame = false;
                }
            }
            if (prevCorns.size() == 0) {
                isTheSame = false;
            }
        }

        enemies.push_back(new Enemy(respInfo.spawnPos, &texDynObjs, *newEnemy));
        enemies.back()->setAngle(respInfo.spawnRotation);
        enemies.back()->setHealth((double)(enemies.back()->getHealth()) *
            multiplier);
        enemies.back()->setDamageValue((double)(enemies.back()->getDamageValue()) *
            multiplier);
    }
}