#include "MenuChooseMode.h"


MenuChooseMode::MenuChooseMode(RenderWindow &window)
{
    MenuPoint point;
    Vector2f textPos;

    point.text.setCharacterSize(48);

    point.text.setString(L"�������� ����� ����");
    point.value = MENU_NULL;
    point.isActive = false;
    textPos.x = window.getSize().x / 2;
    textPos.y = window.getSize().y / 2 - 2 * INTERVAL;
    point.pos = textPos;
    menuPoints.push_back(point);

    point.text.setString(L"����");
    point.value = SCR_GAME_TEST;
    point.isActive = true;
    textPos.y += 2 * INTERVAL;
    point.pos = textPos;
    menuPoints.push_back(point);

    point.text.setString(L"���������");
    point.value = SCR_GAME_SURVIVAL;
    point.isActive = true;
    textPos.y += INTERVAL;
    point.pos = textPos;
    menuPoints.push_back(point);

    point.text.setString(L"�����");
    point.value = SCR_MAIN_MENU;
    point.isActive = true;
    textPos.y += INTERVAL;
    point.pos = textPos;
    menuPoints.push_back(point);
}


int MenuChooseMode::run(RenderWindow &window)
{
    return Menu::run(window, menuPoints);
}