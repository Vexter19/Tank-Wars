#pragma once
#include "GameObject.h"
class MouseCursor :
    public GameObject
{
public:
    MouseCursor(Vector2f pos, Texture &tex, IntRect rect);
    void update(Vector2f pos);
};