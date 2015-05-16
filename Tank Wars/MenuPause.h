#pragma once
#include "Menu.h"

#define SCR_CONTINUE 1

class MenuPause :
    public Menu
{
private:
    std::vector<MenuPoint> menuPoints;
public:
    MenuPause();
    int run(RenderWindow &window);
};

