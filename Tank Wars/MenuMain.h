#pragma once
#include "Menu.h"
class MenuMain :
    public Menu
{
private:
    std::vector<MenuPoint> menuPoints;
public:
    MenuMain(RenderWindow &window);
    int run(RenderWindow &window);
};

