#include "MenuMain.h"


MenuMain::MenuMain(RenderWindow &window) : Menu()
{
    MenuPoint point;
    Vector2f textPos;

    point.text.setCharacterSize(48);

    point.text.setString(L"Главное меню");
    point.value = MENU_NULL;
    point.isActive = false;
    textPos.x = window.getSize().x / 2;
    textPos.y = window.getSize().y / 2 - 2 * INTERVAL;
    point.pos = textPos;
    menuPoints.push_back(point);

    point.text.setString(L"Новая игра");
    point.value = SCR_CHOOSE_MODE;
    point.isActive = true;
    textPos.y += 2 * INTERVAL;
    point.pos = textPos;
    menuPoints.push_back(point);

    point.text.setString(L"Выход");
    point.value = SCR_EXIT;
    point.isActive = true;
    textPos.y += INTERVAL;
    point.pos = textPos;
    menuPoints.push_back(point);
}


int MenuMain::run(RenderWindow &window)
{
    // Выбираем случайную музыку
    srand(time(NULL));
    int rand_theme = rand() % 2;
    switch (rand_theme) {
        case 0:
            music.openFromFile("audio\\main1.wav");
            break;
        case 1:
            music.openFromFile("audio\\main2.wav");
            break;
        default:
            music.openFromFile("audio\\main1.wav");
            break;
    }
    music.setVolume(50);
    music.play();
    return Menu::run(window, menuPoints);
}
