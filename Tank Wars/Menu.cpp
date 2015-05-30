#include "Menu.h"
#include <iostream>

using namespace sf;

Menu::Menu()
{
    alpha_max = 3 * 255;
    alpha_div = 3;
    playing = false;
    backgroundPath = "images\\MenuBackground.png";

    soundBufferMenuArrow.loadFromFile("audio\\menu_arrow.wav");
    soundBufferMenuClick.loadFromFile("audio\\menu_click.wav");
}

Menu::Menu(std::string backgroundPath)
{
    alpha_max = 3 * 255;
    alpha_div = 3;
    playing = false;
    this->backgroundPath = backgroundPath;

    soundBufferMenuArrow.loadFromFile("audio\\menu_arrow.wav");
    soundBufferMenuClick.loadFromFile("audio\\menu_click.wav");
}

int Menu::run(RenderWindow &window, std::vector<MenuPoint> menuPoints)
{
    int alpha = 0;

    Event event;
    bool running = true;

    Texture texGUI;
    texGUI.loadFromFile("images/GUI.png");

    Texture background;
    background.loadFromFile(backgroundPath);

    Sprite sprite;
    sprite.setTexture(background);
    sprite.setColor(Color(255, 255, 255, alpha));
    Vector2f menuPos;
    menuPos.x = view.getCenter().x - view.getSize().x / 2;
    menuPos.y = view.getCenter().y - view.getSize().y / 2;
    sprite.setPosition(menuPos);

    Font font;
    font.loadFromFile(MAIN_FONT);
  
    int choise = MENU_NULL;

    MouseCursor mouse(Vector2f(0, 0), texGUI, IntRect(30, 0, 20, 20));

    Vector2u windowSize;
    windowSize = window.getSize();

    for (std::vector<MenuPoint>::iterator it = menuPoints.begin(); it != menuPoints.end(); it++)  {
        (*it).text.setFont(font);
        //(*it).text.setCharacterSize(MENU_POINT_SIZE);
        (*it).text.setPosition((*it).pos.x + menuPos.x, (*it).pos.y + menuPos.y);
        align(*it);
    }

    if (playing) {
        alpha = alpha_max;
    }
    bool wasPlayed = false;
    while (running) {
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                return (-1);
            }
        }

        if (event.type == Event::MouseButtonPressed &&
            event.key.code == Mouse::Left) {
            if (choise != MENU_NULL) {
                
                sound.setBuffer(soundBufferMenuClick);
                sound.play();

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
                (*it).text.setColor(Color(159, 182, 205, 255));

                sound.setBuffer(soundBufferMenuArrow);
                if (wasPlayed == false){
                    sound.play();
                    wasPlayed = true;
                }

                break;
            }
        }
        if (choise == MENU_NULL) {
            wasPlayed = false;
        }
        // ѕостепенно уменьшаем прозрачность.
        if (alpha < alpha_max) {
            alpha++;
        }
        sprite.setColor(Color(255, 255, 255, alpha / alpha_div));
        
        window.clear();
        window.draw(sprite);

        //  огда прозрачность = 0, отображаем текст.
        for (std::vector<MenuPoint>::iterator it = menuPoints.begin();
            it != menuPoints.end(); it++)  {
            window.draw((*it).text);
        }

        Vector2i mousePos =
            getMouseCoords(Mouse::getPosition(window), windowSize);
        mouse.update((Vector2f)mousePos);
        mouse.draw(window);
        window.display();
    }

    return (-1);
}

void Menu::align(MenuPoint &point)
{
    FloatRect textRect = point.text.getLocalBounds();
    point.text.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);
}