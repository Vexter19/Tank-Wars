#include "MenuSettings.h"


MenuSettings::MenuSettings(RenderWindow &window)
{
    font.loadFromFile(MAIN_FONT);
    Vector2f textPos;

    textPos.x = window.getSize().x / 2 - 150;
    textPos.y = window.getSize().y / 2 - 4 * INTERVAL;

    addSetting(L"Настройки", textPos, false, std::vector<int>{ });
    textPos.y = window.getSize().y / 2 - 2 * INTERVAL;
    addSetting(L"Здесь пока пусто", textPos, false, std::vector<int>{ });
    addSetting(L"Назад", textPos, true, std::vector<int>{ SCR_MAIN_MENU });
}

int MenuSettings::run(RenderWindow &window)
{
    Texture texGUI;
    texGUI.loadFromFile("images/GUI.png");

    MouseCursor mouse(Vector2f(0, 0), texGUI, IntRect(30, 0, 20, 20));

    Event event;

    Vector2u windowSize;
    windowSize = window.getSize();

    int choise = MENU_NULL;

    while (true) {
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

        for (std::vector<Setting>::iterator it = settings.begin();
            it != settings.end(); it++) {
            (*it).text.setColor(Color(255, 255, 255, 255));
            choise = MENU_NULL;
            if (mouse.getSprite().getGlobalBounds().intersects(
                (*it).text.getGlobalBounds()) && (*it).isActive) {

                // Если в векторе значений настройки только одно значение,
                // т.е. данная настройка вовсе и не настройка, то просто
                // выполняем нужное действие
                if ((*it).values.size() == 1) {
                    choise = (*it).values.front();
                    (*it).text.setColor(Color(159, 182, 205, 255));
                    break;
                }
            }
        }

        window.clear();
        for (std::vector<Setting>::iterator it = settings.begin();
            it != settings.end(); it++) {
            window.draw((*it).text);
        }
        Vector2i mousePos =
            getMouseCoords(Mouse::getPosition(window), windowSize);
        mouse.update((Vector2f)mousePos);
        mouse.draw(window);
        window.display();
    }
    return SCR_MAIN_MENU;
}

void MenuSettings::addSetting(std::wstring name, Vector2f &textPos,
    bool isActive, std::vector<int> values) {
    Setting setting;

    setting.text.setCharacterSize(48);
    setting.text.setString(name);
    setting.text.setFont(font);
    textPos.y += 2 * INTERVAL;
    setting.pos = textPos;
    setting.text.setPosition(textPos);
    setting.isActive = isActive;
    setting.values = values;
    settings.push_back(setting);
}