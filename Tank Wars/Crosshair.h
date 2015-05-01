#ifndef CROSSHAIR_H
#define CROSSHAIR_H
#include "Enemy.h"
#include "Player.h"


class Crosshair :
    public GameObject
{
private:
    Font font;
    Text timeBeforeShoot;
    Text tankInfo;
public:
    Crosshair(Vector2f pos, Texture &tex, IntRect rect);
    void update(Vector2f pos, std::list<Enemy*> &enemies, Player &player);
    void draw(RenderWindow &window);
};


#endif // !CROSSHAIR_H