#include "Screens.h"
#include <SFML/Graphics.hpp>


int main()
{
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tank Wars");// , Style::Fullscreen);
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
    GameTest gameTest;
    screens.push_back(&gameTest);

    // Создаём экран "Режим выживания"
    GameSurvival gameSurvival;
    screens.push_back(&gameSurvival);

    while (screen >= 0) {
        screen = screens[screen]->run(window);
    }
    return 0;
}