#pragma once
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
#include "TankInfo.h"
#include <iostream>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include "MenuPause.h"


class Game :
    public cScreen
{
public:
    Game(void);
    int run(Event &event, Clock &clock, Texture &texDynamicObjects,
        Map &map, Player &player, Crosshair &crosshair,  TankInfo &tankInfo,
        std::list<Enemy*> &enemies, std::list<Bullet*> &bullets,
        std::list<GameObject*> &objects, std::list<Animation*> &anims,
        short int direction, short int rotation, RenderWindow &window);
};

