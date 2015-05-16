#ifndef GAME_H
#define GAME_H
#include <list>
#include <vector>
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
#include <SFML/Graphics.hpp>
#include "MenuPause.h"

// Хранит информацию о позиции появления врага
struct RespawnInfo {
    int corn;
    Vector2f spawnPos;
    double spawnRotation;
};

class Game :
    public cScreen
{
public:
    int level;
    bool isInitialized;
    Game(void);
    int run(sf::RenderWindow &window);

    static RespawnInfo getRespawnInfo(int randomizer);
    static bool isTheSameCorn(int a, int b);
    static void createEnemies(std::list<Enemy*> &enemies,
        Texture &texDynObjs, int lvl);
};

#endif // !GAME_H