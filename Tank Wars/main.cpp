#include "Screens.h"
#include <SFML/Graphics.hpp>

int main()
{
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tank Wars");// , Style::Fullscreen);
    window.setMouseCursorVisible(false);

    std::vector<cScreen*> screens;
    int screen = 0;

    Menu menu;
    screens.push_back(&menu);
    Game game;
    screens.push_back(&game);

    while (screen >= 0) {
        screen = screens[screen]->Run(window);
    }
    return 0;
}