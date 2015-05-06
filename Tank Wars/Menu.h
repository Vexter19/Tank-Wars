#ifndef MENU_H
#define MENU_H
#include "cScreen.h"
#include <SFML/Graphics.hpp>
#include "MouseCursor.h"
#include "View.h"
#include <vector>
#include <iterator>

#define MENU_NULL -2
#define MENU_POINT_SIZE 36

struct MenuPoint {
    Text text;
    int value;
};

class Menu :
    public cScreen
{
private:
    int alpha_max;
    int alpha_div;
    bool playing;
    std::vector<MenuPoint> menuPoints;
public:
    Menu(std::vector<MenuPoint> menuPoints);
    int Run(sf::RenderWindow &window);
};

#endif // !MENU_H