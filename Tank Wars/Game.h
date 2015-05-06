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

//#define USSR_T34 texPlayer, IntRect(0, 0, 153, 76), IntRect(0, 78, 174, 55), 52, 13, 36, 36, 100, 100, 4.6, 50, "T-34"
//#define GERMANY_TIGER2 texEnemy, IntRect(0, 0, 190, 100), IntRect(0, 100, 256, 71), 50, 11, 18, 18, 50, 100, 10, 10, "Tiger II"
#define USSR_T34 texPlayer, IntRect(0, 0, 112, 56), IntRect(0, 58, 128, 42), 28, 8, 36, 36, 100, 100, 4.6, 50, "T-34"
#define GERMANY_TIGER2 texEnemy, IntRect(0, 0, 140, 72), IntRect(0, 74, 190, 54), 36, 7, 18, 25, 50, 100, 10, 10, "Tiger II"


class Game :
    public cScreen
{
public:
    bool isInitialized;
    Game(void);
    int Run(sf::RenderWindow &window);
};

#endif // !GAME_H