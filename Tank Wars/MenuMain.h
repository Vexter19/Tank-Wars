#ifndef MENUMAIN_H
#define MENUMAIN_H

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

#endif // !MENUMAIN_H
