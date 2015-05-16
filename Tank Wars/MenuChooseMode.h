#pragma once
#include "Menu.h"


class MenuChooseMode :
    public Menu
{
private:
    std::vector<MenuPoint> menuPoints;
public:
    MenuChooseMode(RenderWindow &window);
    int run(RenderWindow &window);
};

