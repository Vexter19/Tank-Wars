#include "Map.h"


Map::Map(Texture &tex)
{
    sprite.setTexture(tex);
    sprite.setPosition(0, 0);
}

void Map::draw(RenderWindow &window)
{
    window.draw(sprite);
}