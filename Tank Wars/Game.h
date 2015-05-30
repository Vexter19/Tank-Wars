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
#include <SFML/Audio.hpp>
#include "MenuPause.h"
#include "RepairPoint.h"
#include "ChangeTankPoint.h"
#include "ChooseNation.h"

#define MIN_REPAIR_INTERVAL 30.0


class Game :
    public cScreen
{
public:
    Game(void);
    int run(Event &event, Clock &clock, Texture &texDynamicObjects,
        Map &map, Player &player, Crosshair &crosshair,  TankInfo &tankInfo,
        std::list<Enemy*> &enemies, std::list<Bullet*> &bullets,
        std::list<GameObject*> &objects, std::list<Animation*> &anims,
        std::list<RepairPoint*> &repairPoints,
        std::list<ChangeTankPoint*> &changePoints, float &timeBeforeRepairing,
        short int direction, short int rotation, RenderWindow &window, int &kills);
};

