#pragma once
#include <SFML/Graphics.hpp>

sf::View view;

View getViewCoords(float x, float y)
{
    float tempX = x;
    float tempY = y;

    if (x < 683) {
        tempX = 683;
    }

    if (x > 2049) {
        tempX = 2049;
    }

    if (y < 384) {
        tempY = 384;
    }

    if (y > 1152) {
        tempY = 1152;
    }

    view.setCenter(tempX, tempY);
    return view;
}

Vector2i getMouseCoords(Vector2i mouse, Vector2u windowSize)
{
    mouse.x += view.getCenter().x - (windowSize.x / 2);
    mouse.y += view.getCenter().y - (windowSize.y / 2);
    return mouse;
}