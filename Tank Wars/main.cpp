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

    // Создаём экран "Главное меню"
    MenuMain mainMenu(window);
    screens.push_back(&mainMenu);

    // Создаём экран "Выбор режима игры"
    MenuChooseMode chooseModeMenu(window);
    screens.push_back(&chooseModeMenu);

    // Создаём экран "Тестовый режим"
    GameSurvival gameTest;
    screens.push_back(&gameTest);

    // Создаём экран "Режим выживания"
    GameSurvival gameSurvival;
    screens.push_back(&gameSurvival);

    // Создаём экран "Рекорды"
    MenuRecords menuRecords(window);
    screens.push_back(&menuRecords);

    // Создаём экран "Настройки"
    MenuSettings menuSettings(window);
    screens.push_back(&menuSettings);

    while (screen >= 0) {
        screen = screens[screen]->run(window);
    }
    return 0;
}