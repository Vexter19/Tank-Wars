#include "Screens.h"
#include <SFML/Graphics.hpp>


int main()
{
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tank Wars" , Style::Fullscreen);
    window.setMouseCursorVisible(false);

    std::vector<cScreen*> screens;
    int screen = 0;

    std::vector<MenuPoint> menuPoints;
    MenuPoint point;

    // ������ ����� "������� ����"
    menuPoints.clear();
    point.text.setString(L"����� ����");
    point.value = 1;
    menuPoints.push_back(point);
    point.text.setString(L"�����");
    point.value = -1;
    menuPoints.push_back(point);

    Menu mainMenu(menuPoints);
    screens.push_back(&mainMenu);

    // ������ ����� "����"
    Game game;
    screens.push_back(&game);

    // ������ ����� "���� �����"
    menuPoints.clear();
    point.text.setString(L"����������");
    point.value = 1;
    menuPoints.push_back(point);
    point.text.setString(L"�����");
    point.value = -1;
    menuPoints.push_back(point);

    Menu pauseMenu(menuPoints);
    screens.push_back(&pauseMenu);

    while (screen >= 0) {
        screen = screens[screen]->Run(window);
    }
    return 0;
}