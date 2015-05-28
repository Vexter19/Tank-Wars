#ifndef MENUPAUSE_H
#define MENUPAUSE_H

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

#endif // !MENUPAUSE_H
