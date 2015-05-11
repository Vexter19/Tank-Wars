#ifndef GAME_H
#define GAME_H
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
#include <SFML/Graphics.hpp>
#include "Screens.h"

// Хранит информацию о позиции появления врага
struct RespawnInfo {
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
    int Run(sf::RenderWindow &window);

    static RespawnInfo getRespawnInfo(int randomizer);
};

#endif // !GAME_H