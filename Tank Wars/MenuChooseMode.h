#ifndef MENUCHOOSEMODE_H
#define MENUCHOOSEMODE_H

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


#endif // !MENUCHOOSEMODE_H
