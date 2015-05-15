#include "Map.h"


Map::Map(Texture &background, Texture &texObjects,
    std::list<GameObject*> &objects, int lvl)
{
    this->background.setTexture(background);
    this->background.setPosition(0, 0);
    switch (lvl) {
    case 0: objects.push_back(new GameObject(Vector2f(600, 600), texObjects, IntRect(0, 0, 68, 63)));
        objects.push_back(new GameObject(Vector2f(1000, 1500), texObjects, IntRect(0, 0, 68, 63)));
        objects.push_back(new GameObject(Vector2f(1000, 600), texObjects, IntRect(72, 0, 75, 164)));
    }
}

void Map::draw(RenderWindow &window, std::list<GameObject*> &objects)
{
    window.draw(background);
    for (std::list<GameObject*>::iterator it = objects.begin();
        it != objects.end(); ++it) {
        //GameObject *obj_bullet = *it;
        (*it)->draw(window);
    }
}

Vector2f Map::getSize()
{
    Vector2f result;
    result.x = background.getLocalBounds().width;
    result.y = background.getLocalBounds().height;
    return result;
}