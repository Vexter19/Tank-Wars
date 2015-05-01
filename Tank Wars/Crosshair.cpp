#include "Crosshair.h"


Crosshair::Crosshair(Vector2f pos, Texture &tex, IntRect rect) :
GameObject(pos, tex, rect)
{
    font.loadFromFile("Calibrib.ttf");

    timeBeforeShoot.setFont(font);
    timeBeforeShoot.setCharacterSize(16);

    tankInfo.setFont(font);
    tankInfo.setCharacterSize(16);
}


void Crosshair::update(Vector2f pos, std::list<Enemy*> &enemies, Player &player)
{
    // По умолчанию ничего не отбражаем над прицелом.
    tankInfo.setString("");

    // Цвет прицела по умолчанию - белый.
    sprite.setColor(Color::White);

    // Если прицел наведён на врага - цвет красный.
    for (std::list<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); ++it) {
        GameObject *obj = *it;
        if (checkCollision(obj) == true) {
            sprite.setColor(Color::Red);

            tankInfo.setString((*it)->getTankInfo());
            tankInfo.setColor(Color::Red);
        }
    }

    // Если прицел наведён на игрока - цвет зелёный.
    GameObject *obj = &player;
    if (checkCollision(obj) == true) {
        sprite.setColor(Color::Blue);

        std::string temp = player.getTankInfo();
        tankInfo.setString(player.getTankInfo());
        tankInfo.setColor(Color::Blue);
    }
    sprite.setPosition(pos.x, pos.y);

    if (player.getReaminingTime() != 0) {
        timeBeforeShoot.setColor(Color::Red);
        timeBeforeShoot.setString(numToStr(player.getReaminingTime()));
    } else {
        timeBeforeShoot.setString("");
    }
    tankInfo.setPosition(pos.x - 36, pos.y - 36);
    timeBeforeShoot.setPosition(pos.x + 8, pos.y + 8);
}

void Crosshair::draw(RenderWindow &window)
{
    GameObject::draw(window);
    window.draw(timeBeforeShoot);
    window.draw(tankInfo);
}