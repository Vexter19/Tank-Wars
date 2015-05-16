#include "MenuPause.h"


MenuPause::MenuPause()
{
    
}


int MenuPause::run(RenderWindow &window)
{
    MenuPoint point;
    Vector2f textPos;

    point.text.setString(L"�����");
    point.value = MENU_NULL;
    point.isActive = false;
    textPos.x = window.getSize().x / 2 - 50;
    textPos.y = window.getSize().y / 2 - 100;
    point.pos = textPos;
    menuPoints.push_back(point);

    point.text.setString(L"����������");
    point.value = SCR_CONTINUE;
    point.isActive = true;
    textPos.y += 50;
    point.pos = textPos;
    menuPoints.push_back(point);

    point.text.setString(L"������� ����");
    point.value = SCR_MAIN_MENU;
    point.isActive = true;
    textPos.y += 50;
    point.pos = textPos;
    menuPoints.push_back(point);

    point.text.setString(L"�����");
    point.value = SCR_EXIT;
    point.isActive = true;
    textPos.y += 50;
    point.pos = textPos;
    menuPoints.push_back(point);
    return Menu::run(window, menuPoints);
}
