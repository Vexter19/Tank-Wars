#include "MenuSettings.h"
#include <iostream>


MenuSettings::MenuSettings(RenderWindow &window)
{
    font.loadFromFile(MAIN_FONT);
    Vector2f textPos;

    textPos.x = window.getSize().x / 2 - 150;
    textPos.y = window.getSize().y / 2 - 5 * INTERVAL;

    addSetting(ID_NOT_A_SETTING, L"Настройки", textPos, false);
    textPos.y = window.getSize().y / 2 - 2 * INTERVAL;
    addSetting(ID_SOUND, L"Звук", textPos, true);
    addSetting(ID_QUALITY ,L"Улучшенная графика", textPos, true);
    addSetting(ID_FULLSCREEN ,L"Полный экран", textPos, true);
    addSetting(ID_VSYNC, L"Верт. синх.", textPos, true);
    textPos.x -= 100;
    addSetting(SAVE, L"Сохранить", textPos, true);
    textPos.y -= INTERVAL;
    textPos.x += 400;
    addSetting(BACK, L"Назад", textPos, true);

    loadSettings(window);
}

int MenuSettings::run(RenderWindow &window)
{
    Texture texBackground;
    texBackground.loadFromFile("images//MenuBackground.png");
    Sprite background;
    background.setTexture(texBackground);

    Texture texGUI;
    texGUI.loadFromFile("images/GUI.png");

    MouseCursor mouse(Vector2f(0, 0), texGUI, IntRect(30, 0, 20, 20));

    Event event;

    Vector2u windowSize;
    windowSize = window.getSize();

    int choise = MENU_NULL;

    Vector2f menuPos;
    menuPos.x = view.getCenter().x - view.getSize().x / 2;
    menuPos.y = view.getCenter().y - view.getSize().y / 2;
    background.setPosition(menuPos);

    while (true) {
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                return (-1);
            }

            if (event.type == Event::MouseButtonPressed &&
                event.key.code == Mouse::Left) {
                if (choise != MENU_NULL) {
                    if (choise == SAVE) {
                        saveSettings(window);
                    } else if (choise == SCR_MAIN_MENU) {
                        return SCR_MAIN_MENU;
                    } else {
                        (settings[choise]).value =
                            ((settings[choise]).value == true) ? false : true;
                    }
                    sound.setBuffer(soundBufferMenuClick);
                    sound.play();
                }
            }
        }
        
        choise = MENU_NULL;
        for (std::vector<Setting>::iterator it = settings.begin();
            it != settings.end(); it++) {

            (*it).text.setPosition((*it).pos.x + menuPos.x, (*it).pos.y + menuPos.y);

            if (((*it).id >= 1) && ((*it).id <= 4)) {
                (*it).text.setString((*it).name + L"  " + getNameOfValue(it));
            }

            (*it).text.setColor(Color(255, 255, 255, 255));

            if (mouse.getSprite().getGlobalBounds().intersects(
                (*it).text.getGlobalBounds()) && (*it).isActive) {

                (*it).text.setColor(Color(159, 182, 205, 255));

                if ((*it).id == SAVE) {
                    choise = SCR_MAIN_MENU;
                }
                if ((*it).id == BACK) {
                    choise = SCR_MAIN_MENU;
                } else {
                    choise = (*it).id;
                }
            }
        }

        window.clear();
        window.draw(background);
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

void MenuSettings::addSetting(int id,std::wstring name, Vector2f &textPos,
    bool isActive) {
    Setting setting;

    setting.text.setCharacterSize(48);
    setting.text.setString(name);
    setting.text.setFont(font);
    setting.name = name;
    textPos.y += INTERVAL;
    setting.pos = textPos;
    setting.text.setPosition(textPos);
    setting.isActive = isActive;
    setting.id = id;
    settings.push_back(setting);
}

void  MenuSettings::saveSettings(RenderWindow &window)
{
    int fullscreen = 1;
    int vsync = 1;

    for (std::vector<Setting>::iterator it = settings.begin();
        it != settings.end(); it++) {
        if ((*it).id == ID_SOUND) {
            isSoundOn = (*it).value;
        }
        if ((*it).id == ID_QUALITY) {
            graphicsSettings = (*it).value;
        }
        if ((*it).id == ID_FULLSCREEN) {
            fullscreen = (*it).value;
        }
        if ((*it).id == ID_VSYNC) {
            vsync = (*it).value;
        }
    }

    if (fullscreen == 1) {
        window.create(VideoMode::getDesktopMode(), "Tank Wars", Style::Fullscreen);
    } else {
        window.create(VideoMode::getDesktopMode(), "Tank Wars", Style::Default);
    }

    if (vsync == 1) {
        window.setVerticalSyncEnabled(true);
    } else {
        window.setVerticalSyncEnabled(false);
    }
    window.setMouseCursorVisible(false);
    //window.setFramerateLimit(60);

    std::ofstream fout("data\\settings.dat", std::ios::out);
    fout << isSoundOn << " " << graphicsSettings  << " " <<
        fullscreen << " " << vsync << std::endl;
    fout.close();
}

void MenuSettings::loadSettings(RenderWindow &window)
{
    std::ifstream fin("data\\settings.dat", std::ios::in);
    if (fin.is_open()) {
        for (std::vector<Setting>::iterator it = settings.begin();
            it != settings.end(); it++) {
            if (((*it).id >= ID_SOUND) && ((*it).id <= ID_VSYNC)) {
                int value;
                fin >> value;
                (*it).value = value;
            }
        }
        fin.close();
        saveSettings(window);
    } else {
        return;
    }

}

std::wstring MenuSettings::getNameOfValue(std::vector<Setting>::iterator it) {
    if ((*it).value == true) {
        return L"вкл";
    } else {
        return L"выкл";
    }
}