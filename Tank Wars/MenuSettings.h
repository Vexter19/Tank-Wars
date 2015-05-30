#ifndef MENUSETTINGS_H
#define MENUSETTINGS_H

#include "cScreen.h"
#include <SFML/Graphics.hpp>
#include "global.h"
#include "Menu.h"
#include "MouseCursor.h"
#include "View.h"

using namespace sf;


struct Setting
{
    Text text;
    Vector2f pos;
    bool isActive;
    std::vector<int> values;
};

class MenuSettings :
    public cScreen
{
private:
    Font font;
    std::vector<Setting> settings;
    void addSetting(std::wstring name, Vector2f &textPos, bool isActive,
        std::vector<int> values);
public:
    MenuSettings(RenderWindow &window);
    int run(RenderWindow &window);
};


#endif // !MENUSETTINGS_H
