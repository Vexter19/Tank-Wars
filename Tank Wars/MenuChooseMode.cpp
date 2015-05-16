#include "MenuChooseMode.h"


MenuChooseMode::MenuChooseMode(RenderWindow &window)
{
    MenuPoint point;
    Vector2f textPos;

    point.text.setString(L"Выберите режим игры");
    point.value = MENU_NULL;
    point.isActive = false;
    textPos.x = window.getSize().x / 2 - 50;
    textPos.y = window.getSize().y / 2 - 100;
    point.pos = textPos;
    menuPoints.push_back(point);

    point.text.setString(L"Тест");
    point.value = SCR_GAME_TEST;
    point.isActive = true;
    textPos.y += 50;
    point.pos = textPos;
    menuPoints.push_back(point);

    point.text.setString(L"Выживание");
    point.value = SCR_GAME_SURVIVAL;
    point.isActive = true;
    textPos.y += 50;
    point.pos = textPos;
    menuPoints.push_back(point);
}


int MenuChooseMode::run(RenderWindow &window)
{
    return Menu::run(window, menuPoints);
}
