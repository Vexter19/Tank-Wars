#include "GameSurvival.h"


Game::Game(void)
{
    soundBufferShoot.loadFromFile("audio\\shot_light.wav");
    soundBufferVehicle.loadFromFile("audio\\vehicle.wav");
    soundBufferRepairOn.loadFromFile("audio\\repaired.wav");
    soundBufferIdle.loadFromFile("audio\\idle.wav");

    soundShoot.setBuffer(soundBufferShoot);

    soundVehicle.setBuffer(soundBufferVehicle);
    soundVehicle.setLoop(true);

    soundPlayerVehicle.setBuffer(soundBufferVehicle);
    soundPlayerVehicle.setVolume(50);
    soundPlayerVehicle.setLoop(true);

    soundIdle.setBuffer(soundBufferIdle);
    soundIdle.setLoop(true);

    soundPlayerIdle.setBuffer(soundBufferIdle);
    soundPlayerIdle.setVolume(50);
    soundPlayerIdle.setLoop(true);

    soundRepairOn.setBuffer(soundBufferRepairOn);
}

int Game::run(Event &event, Clock &clock, Texture &texDynamicObjects,
    Map &map, Player &player, Crosshair &crosshair, TankInfo &tankInfo,
    std::list<Enemy*> &enemies, std::list<Bullet*> &bullets,
    std::list<GameObject*> &objects, std::list<Animation*> &anims,
    std::list<RepairPoint*> &repairPoints,
    std::list<ChangeTankPoint*> &changePoints, float &timeBeforeRepairing,
    short int direction, short int rotation, RenderWindow &window, int &kills)
{
    Vector2u windowSize;

    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            return -1;
        }
    }

    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
        // Создаём экран "Меню паузы"
        std::vector<MenuPoint> menuPoints;
        MenuPoint point;

        soundVehicle.stop();
        soundPlayerVehicle.stop();

        point.text.setString(L"Продолжить");
        point.value = 1;
        menuPoints.push_back(point);
        point.text.setString(L"Выход");
        point.value = -1;
        menuPoints.push_back(point);

        MenuPause pauseMenu;
        switch (pauseMenu.run(window)) {
            case 1:
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

    if (Mouse::isButtonPressed(Mouse::Left)) {
        player.fire(bullets, texDynamicObjects);
    }

    if (event.type == Event::MouseButtonPressed &&
        event.key.code == Mouse::Right) {
        enemies.clear();
    }

    // Зум. Работает косячно.
    if (event.type == Event::MouseWheelMoved) {
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
    }


    double time = (double)clock.getElapsedTime().asMicroseconds();
    time = time / 1000;
    clock.restart();

    timeBeforeRepairing -= time / 1000;
    if (timeBeforeRepairing < 0) {
        timeBeforeRepairing = 0;
    }

    

    view = getViewCoords(player.getPos().x, player.getPos().y);

    for (std::list<Bullet*>::iterator it_bullets = bullets.begin();
        it_bullets != bullets.end();) {
        Bullet* b = *it_bullets;

        if (b->isAlive() == false) {
            it_bullets = bullets.erase(it_bullets);
            delete b;
        } else {
            it_bullets++;
        }
    }

    for (std::list<Animation*>::iterator it_anims = anims.begin();
        it_anims != anims.end();) {
        Animation *a = *it_anims;

        if ((*it_anims)->isAlive() == false) {
            it_anims = anims.erase(it_anims);
            delete a;
        } else {
            it_anims++;
        }
    }

    for (std::list<Enemy*>::iterator it_enemies = enemies.begin();
        it_enemies != enemies.end();) {
        Enemy *e = *it_enemies;

        if ((*it_enemies)->isAlive() == false) {
            it_enemies = enemies.erase(it_enemies);
            delete e;
            ++kills;
        } else {
            it_enemies++;
        }
    }
    
    windowSize = window.getSize();
    Vector2i mousePos = getMouseCoords(Mouse::getPosition(window), windowSize);
    player.update(time, direction, rotation, objects, enemies, bullets, anims);
    player.rotateTurrel(mousePos, rotation, direction);

    window.setView(view);
    window.clear();

    map.draw(window, objects);

    for (std::list<RepairPoint*>::iterator it_repairs = repairPoints.begin();
        it_repairs != repairPoints.end();) {
        RepairPoint *rep = *it_repairs;

        if ((*it_repairs)->isAlive() == false) {
            it_repairs = repairPoints.erase(it_repairs);
            delete rep;
        } else {
            it_repairs++;
        }
    }

    for (std::list<RepairPoint*>::iterator it_repairs = repairPoints.begin();
        it_repairs != repairPoints.end(); it_repairs++) {
        bool isRepaired = (*it_repairs)->repair(player, time);
        (*it_repairs)->draw(window);
        if (isRepaired == true) {
            timeBeforeRepairing = MIN_REPAIR_INTERVAL;
        }
    }

    for (std::list<ChangeTankPoint*>::iterator it_change = changePoints.begin();
        it_change != changePoints.end();) {
        ChangeTankPoint *change = *it_change;

        if ((*it_change)->isAlive() == false) {
            it_change = changePoints.erase(it_change);
            delete change;
        } else {
            it_change++;
        }
    }

    for (std::list<ChangeTankPoint*>::iterator it_change = changePoints.begin();
        it_change != changePoints.end(); it_change++) {
        (*it_change)->change(window, player, time);
        (*it_change)->draw(window);
    }

   // std::cout << timeBeforeRepairing << "   " << time << "  " << repairPoints.size() << std::endl;  
   

    player.draw(window);
    for (std::list<Enemy*>::iterator it_enemies = enemies.begin();
        it_enemies != enemies.end(); it_enemies++) {
        Tank playerTank = player;
        (*it_enemies)->update(time, playerTank, bullets, objects, anims, enemies);
        (*it_enemies)->draw(window);
        // window.draw((*it_enemies)->bigSprite); // Потом удалить
    }

    for (std::list<Bullet*>::iterator it_bullets = bullets.begin();
        it_bullets != bullets.end(); it_bullets++) {
        (*it_bullets)->update(time, view, window, objects, anims);
        (*it_bullets)->draw(window);
    }

    for (std::list<Animation*>::iterator it_anims = anims.begin();
        it_anims != anims.end(); it_anims++) {
        (*it_anims)->update(time);
        (*it_anims)->draw(window);
    }

    crosshair.update((Vector2f)mousePos, enemies, player);
    crosshair.draw(window);

    tankInfo.update(player);
    tankInfo.draw(window);

    return MENU_NULL;
}
