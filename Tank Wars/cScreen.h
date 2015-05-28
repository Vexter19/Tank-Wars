#ifndef CSCREEN_H
#define CSCREEN_H
#include "SFML/Graphics.hpp"

#define SCR_EXIT -1
#define SCR_MAIN_MENU 0
#define SCR_CHOOSE_MODE 1
//#define SCR_CHOOSE_NATION 2
#define SCR_GAME_TEST 2
#define SCR_GAME_SURVIVAL 3
#define SCR_MENU_LOSE 4

class cScreen
{
public:
    virtual int run(sf::RenderWindow &window) = 0;
};

#endif // !CSCREEN_H