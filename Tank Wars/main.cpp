#include <list>
#include <iterator>
#include "Player.h"
#include "Enemy.h"
#include "Map.h"
#include "View.h"
#include "Bullet.h"
#include "Collision.h"
#include <iostream>

#define WINDOW_WIDTH 1366
#define WINDOW_HEIGHT 768

#define USSR_T34 texPlayer, IntRect(0, 0, 153, 76), IntRect(0, 78, 174, 55), 52 , 36, 36, 100, 100
#define GERMANY_TIGER2 texEnemy, IntRect(0, 0, 190, 100), IntRect(0, 100, 256, 71), 50 , 18, 18, 50, 100

int main()
{
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tank Wars" , Style::Fullscreen);

    Clock clock;

    Texture texPlayer;
    texPlayer.loadFromFile("images/T-34.png");
    Texture texEnemy;
    texEnemy.loadFromFile("images/TigerII.png");
    Texture texDynamicObjects;
    texDynamicObjects.loadFromFile("images/DynamicObjects.png");
    Texture texMap;
    texMap.loadFromFile("images/grass.png");

    std::list<Enemy*> enemies;
    std::list<Enemy*>::iterator it_enemies;

    std::list<Bullet*> bullets;
    std::list<Bullet*>::iterator it_bullets;

    std::list<GameObject*> staticObjects;
    std::list<GameObject*>::iterator it_static_objects;

    std::list<Animation*> anims;
    std::list<Animation*>::iterator it_anims;

    Map grass(texMap);

    Player player(Vector2f(500, 500), USSR_T34);

    enemies.push_back(new Enemy(Vector2f(1000, 1000), GERMANY_TIGER2));

    Vector2u windowSize;
    view.reset(FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));

    Event event;

    /* direction - задаёт направление движения танка игрока:
    Принимает значение 1, если нажата кнопка W
    и -1, если нажата S */
    short int direction = 0;
    /* rotation - задаёт направление поворота танка игрока:
    Принимает значение 1, если нажата кнопка D
    и -1, если нажата A */
    short int rotation = 0;

    while (window.isOpen()) { 
        while (window.pollEvent(event)) {
            if ((event.type == Event::Closed) ||
                (Keyboard::isKeyPressed(Keyboard::Escape))) {
                window.close();
            }

            if (event.type == Event::MouseButtonPressed) {
                if (event.key.code == Mouse::Left) {
                    bullets.push_back(new Bullet(player.getPos(), player.getTurrelDir(), &texDynamicObjects, IntRect(0, 0, 17, 5)));
                }
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

        double time = (double)clock.getElapsedTime().asMicroseconds();
        time = time / 1000;
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
        Vector2i mousePos = getMouseCoords(Mouse::getPosition(window), windowSize);
        

        player.update(time, direction, rotation, enemies);
        player.rotateTurrel(mousePos);
        
        window.setView(view);
        window.clear();
 
        grass.draw(window);
        player.draw(window);
        for (it_enemies = enemies.begin(); it_enemies != enemies.end(); it_enemies++) {
            Tank playerTank = player;
            (*it_enemies)->update(time, playerTank);
            (*it_enemies)->draw(window);
        }
        
        for (it_bullets = bullets.begin(); it_bullets != bullets.end(); it_bullets++) {
            (*it_bullets)->update(time, view, window, player, enemies, anims);
            (*it_bullets)->draw(window);
        }

        for (it_anims = anims.begin(); it_anims != anims.end(); it_anims++) {
            (*it_anims)->update(time);
            (*it_anims)->draw(window);
        }
        
        window.display();
    }
    return 0;
}