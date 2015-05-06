#include "MouseCursor.h"


MouseCursor::MouseCursor(Vector2f pos, Texture &tex, IntRect rect) :
GameObject(pos, tex, rect)
{
    sprite.setOrigin(0, 0);
}

void MouseCursor::update(Vector2f pos)
{
    sprite.setPosition(pos);
}