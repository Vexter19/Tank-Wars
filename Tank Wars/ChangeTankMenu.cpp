#include "ChangeTankMenu.h"


ChangeTankMenu::ChangeTankMenu(Vector2f pos, int nation, Player &player) :
GameObject(pos, NULL, IntRect(0, 0, 160, 100))
{
    position = pos;
    if (nation == USSR) {
        texture.loadFromFile("images\tiles\\ussr.png");
        texTank1.loadFromFile("images\tiles\T-46.png");
        texTank2.loadFromFile("images\tiles\T-34.png");
        texTank3.loadFromFile("images\tiles\KV1.png");
        texTank4.loadFromFile("images\tiles\IS.png");
        texTank5.loadFromFile("images\tiles\IS-3.png");

        TankTile tempTank;
        tempTank = { &texTank1, 1, &ussrT46 };
        tanks.push_back(&tempTank);

        tempTank = { &texTank2, 2, &ussrT34 };
        tanks.push_back(&tempTank);

        tempTank = { &texTank3, 3, &ussrKV1 };
        tanks.push_back(&tempTank);

        tempTank = { &texTank4, 4, &ussrIS };
        tanks.push_back(&tempTank);

        tempTank = { &texTank5, 5, &ussrIS3 };
        tanks.push_back(&tempTank);

    } else {
        texture.loadFromFile("images\tiles\germany.png");
        texTank1.loadFromFile("images\tiles\PZ1C.png");
        texTank2.loadFromFile("images\tiles\PZIV.png");
        texTank3.loadFromFile("images\tiles\TigerI.png");
        texTank4.loadFromFile("images\tiles\TigerII.png");
        texTank5.loadFromFile("images\tiles\Maus.png");

        TankTile tempTank;
        tempTank = { &texTank1, 1, &germanyPz1C };
        tanks.push_back(&tempTank);

        tempTank = { &texTank2, 2, &germanyPZIV };
        tanks.push_back(&tempTank);

        tempTank = { &texTank3, 3, &germanyTiger1 };
        tanks.push_back(&tempTank);

        tempTank = { &texTank4, 4, &germanyTiger2 };
        tanks.push_back(&tempTank);

        tempTank = { &texTank5, 5, &germanyMaus };
        tanks.push_back(&tempTank);
    }

    int playerLevel = player.getLevel();

    sprite.setTexture(texture);
}


void ChangeTankMenu::update()
{
    
}


void draw();
