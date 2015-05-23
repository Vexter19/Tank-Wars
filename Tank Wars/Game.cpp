#include "GameSurvival.h"


Game::Game(void)
{
}

int Game::run(Event &event, Clock &clock, Texture &texDynamicObjects,
    Map &map, Player &player, Crosshair &crosshair, TankInfo &tankInfo,
    std::list<Enemy*> &enemies, std::list<Bullet*> &bullets,
    std::list<GameObject*> &objects, std::list<Animation*> &anims,
    short int direction, short int rotation, RenderWindow &window)
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
    if (event.type == Event::MouseButtonPressed &&
        event.key.code == Mouse::Left) {
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

    window.display();
    return MENU_NULL;
}
