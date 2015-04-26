#pragma once
#include <SFML\Graphics.hpp>

using namespace sf;

class Map
{

private:
    Texture texture;
    Sprite sprite;

public:
    Map(Texture &tex);
    void draw(RenderWindow &window);
};

