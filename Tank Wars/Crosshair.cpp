#include "Crosshair.h"


Crosshair::Crosshair(Vector2f pos, Texture &tex, IntRect rect) :
GameObject(pos, tex, rect)
{
}


void Crosshair::update(Vector2f pos, std::list<Enemy*> &enemies, Player &player)
{
    // ���� ������� �� ��������� - �����.
    sprite.setColor(Color::White);

    // ���� ������ ������ �� ����� - ���� �������.
    for (std::list<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); ++it) {
        GameObject *obj = *it;
        if (checkCollision(obj) == true) {
            sprite.setColor(Color::Red);
        }
    }

    // ���� ������ ������ �� ������ - ���� ������.
    GameObject *obj = &player;
    if (checkCollision(obj) == true) {
        sprite.setColor(Color::Green);
    }
    sprite.setPosition(pos.x, pos.y);
}
