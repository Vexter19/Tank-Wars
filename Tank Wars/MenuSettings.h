#ifndef MENUSETTINGS_H
#define MENUSETTINGS_H

#include "cScreen.h"
#include <SFML/Graphics.hpp>
#include "global.h"
#include "Menu.h"
#include "MouseCursor.h"
#include "View.h"
#include <fstream>

#define ID_NOT_A_SETTING -1
#define ID_SOUND 1
#define ID_QUALITY 2
#define ID_FULLSCREEN 3
#define ID_VSYNC 4
#define BACK 5
#define SAVE 6

using namespace sf;


struct Setting
{
    std::wstring name;
    int id;
    Text text;
    Vector2f pos;
    bool isActive;
    bool value;
};

class MenuSettings :
    public cScreen
{
private:
    Font font;
    std::vector<Setting> settings;
    void addSetting(int id, std::wstring name, Vector2f &textPos, bool isActive);
    void saveSettings(RenderWindow &window);
    void loadSettings(RenderWindow &window);
    std::wstring getNameOfValue(std::vector<Setting>::iterator it);
public:
    MenuSettings(RenderWindow &window);
    int run(RenderWindow &window);
};


#endif // !MENUSETTINGS_H
