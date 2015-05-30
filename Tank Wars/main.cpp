#include "Screens.h"
#include <SFML/Graphics.hpp>



int main()
{
    RenderWindow window(VideoMode::getDesktopMode(), "Tank Wars", Style::Fullscreen);
    window.setMouseCursorVisible(false);

    view.setCenter(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    view.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    std::vector<cScreen*> screens;
    int screen = 0;

    std::vector<MenuPoint> menuPoints;
    MenuPoint point;

    // ������ ����� "������� ����"
    MenuMain mainMenu(window);
    screens.push_back(&mainMenu);

    // ������ ����� "����� ������ ����"
    MenuChooseMode chooseModeMenu(window);
    screens.push_back(&chooseModeMenu);

    // ������ ����� "�������� �����"
    GameSurvival gameTest;
    screens.push_back(&gameTest);

    // ������ ����� "����� ���������"
    GameSurvival gameSurvival;
    screens.push_back(&gameSurvival);

    // ������ ����� "�������"
    MenuRecords menuRecords(window);
    screens.push_back(&menuRecords);

    // ������ ����� "���������"
    MenuSettings menuSettings(window);
    screens.push_back(&menuSettings);

    while (screen >= 0) {
        screen = screens[screen]->run(window);
    }
    return 0;
}