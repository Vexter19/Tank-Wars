#pragma once
#include <SFML\Graphics.hpp>
#include "GameObject.h"

using namespace sf;

class Map
{

private:
    Texture texture;
    Sprite background;

public:
    Map(Texture &background, Texture &texObjects,
        std::list<GameObject*> &objects, int lvl);
    void draw(RenderWindow &window, std::list<GameObject*> &objects);
};

