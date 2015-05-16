#include "Menu.h"
#include <iostream>

using namespace sf;

Menu::Menu()
{
    alpha_max = 3 * 255;
    alpha_div = 3;
    playing = false;
}

int Menu::run(RenderWindow &window, std::vector<MenuPoint> menuPoints)
{
    int alpha = 0;

    Event event;
    bool running = true;

    Texture texGUI;
    texGUI.loadFromFile("images/GUI.png");

    Texture background;
    background.loadFromFile("images/MenuBackground.png");

    Sprite sprite;
    sprite.setTexture(background);
    sprite.setColor(Color(255, 255, 255, alpha));
    Vector2f menuPos;
    menuPos.x = view.getCenter().x - view.getSize().x / 2;
    menuPos.y = view.getCenter().y - view.getSize().y / 2;
    sprite.setPosition(menuPos);
    std::cout << view.getCenter().x << "  " << view.getCenter().y << std::endl;

    Font font;
    font.loadFromFile("calibrib.ttf");
  
    int choise = MENU_NULL;

    MouseCursor mouse(Vector2f(0, 0), texGUI, IntRect(30, 0, 20, 20));

    Vector2u windowSize;
    windowSize = window.getSize();

    for (std::vector<MenuPoint>::iterator it = menuPoints.begin(); it != menuPoints.end(); it++)  {
        (*it).text.setFont(font);
        (*it).text.setCharacterSize(MENU_POINT_SIZE);
        (*it).text.setPosition((*it).pos.x + menuPos.x, (*it).pos.y + menuPos.y);
    }

    if (playing) {
        alpha = alpha_max;
    }

    while (running) {
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                return (-1);
            }
        }

        if (event.type == Event::MouseButtonPressed &&
            event.key.code == Mouse::Left) {
            if (choise != MENU_NULL) {
                return choise;
            }
        }

        for (std::vector<MenuPoint>::iterator it = menuPoints.begin();
            it != menuPoints.end(); it++) {
            (*it).text.setColor(Color(255, 255, 255, 255));
            choise = MENU_NULL;
            if (mouse.getSprite().getGlobalBounds().intersects(
                (*it).text.getGlobalBounds()) && (*it).isActive)
            {
                choise = (*it).value;
                (*it).text.setColor(Color(255, 0, 0, 255));
                break;
            }
        }

        // ѕостепенно уменьшаем прозрачность.
        if (alpha < alpha_max) {
            alpha++;
        }
        sprite.setColor(Color(255, 255, 255, alpha / alpha_div));

        
        window.clear();
        window.draw(sprite);

        //  огда прозрачность = 0, отображаем текст.
        //if (alpha == alpha_max) {
            for (std::vector<MenuPoint>::iterator it = menuPoints.begin();
                it != menuPoints.end(); it++)  {
               // std::cout << (*it).text.getPosition().x << "  " << (*it).text.getPosition().y << std::endl;
                window.draw((*it).text);
            }
        //}
        Vector2i mousePos =
            getMouseCoords(Mouse::getPosition(window), windowSize);
        mouse.update((Vector2f)mousePos);
        mouse.draw(window);
        window.display();
    }

    return (-1);
}