#include <list>
#include <iterator>
#include "Player.h"
#include "Enemy.h"
#include "Map.h"
#include "View.h"
#include "Bullet.h"
#include "Collision.h"
#include "Crosshair.h"
#include <iostream>
#include <SFML/Window/Event.hpp>

#define USSR_T34 texPlayer, IntRect(0, 0, 153, 76), IntRect(0, 78, 174, 55), 52, 13, 36, 36, 100, 100, 4.6, 50, "T-34"
#define GERMANY_TIGER2 texEnemy, IntRect(0, 0, 190, 100), IntRect(0, 100, 256, 71), 50, 11, 18, 18, 50, 100, 10, 35, "Tiger II"

int main()
{
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tank Wars", Style::Fullscreen);
    window.setMouseCursorVisible(false);

    Event event;

    /*while (true) {
        Texture texMenu;
        texMenu.loadFromFile("images/grass.png");
        Sprite menu;

        while (window.pollEvent(event)) {
        if ((event.type == Event::Closed) ||
        (Keyboard::isKeyPressed(Keyboard::Escape))) {
        window.close();
        }
        }
        menu.setTexture(texMenu);
        menu.setPosition(0, 0);
        window.draw(menu);
        window.display();
        }*/

    Clock clock;

    Texture texPlayer;
    texPlayer.loadFromFile("images/T-34.png");
    Texture texEnemy;
    texEnemy.loadFromFile("images/TigerII.png");
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

    Player player(Vector2f(500, 500), USSR_T34);

    Crosshair crosshair(Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), texGUI, IntRect(0, 0, 24, 24));

    enemies.push_back(new Enemy(Vector2f(1000, 1000), &texDynamicObjects, GERMANY_TIGER2));

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

    IntRect rectTest;
    rectTest.left = 100;
    rectTest.top = 100;
    rectTest.width = 100;

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if ((event.type == Event::Closed) ||
                (Keyboard::isKeyPressed(Keyboard::Escape))) {
                window.close();
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
        //std::cout << time << std::endl;
        clock.restart();

        getViewCoords(player.getPos().x, player.getPos().y);

        for (it_bullets = bullets.begin(); it_bullets != bullets.end();) {
            Bullet *b = *it_bullets;

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

        windowSize = window.getSize();
        //Vector2i mousePos = getMouseCoords(Mouse::getPosition(window), (Vector2u)view.getSize());
        Vector2i mousePos = getMouseCoords(Mouse::getPosition(window), windowSize);
        player.update(time, direction, rotation, objects, enemies, bullets, anims);
        player.rotateTurrel(mousePos);
        
        window.setView(view);
        window.clear();
 
        map.draw(window, objects);
        player.draw(window);
        for (it_enemies = enemies.begin(); it_enemies != enemies.end(); it_enemies++) {
            Tank playerTank = player;
            (*it_enemies)->update(time, playerTank, bullets, objects, anims);
            (*it_enemies)->draw(window);
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