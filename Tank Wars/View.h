#pragma once
#include <SFML/Graphics.hpp>

#define WINDOW_WIDTH 1366
#define WINDOW_HEIGHT 768

sf::View view;

const double mapWidth = 2732;
const double mapHeight = 1536;

View getViewCoords(double x, double y)
{
    double tempX = x;
    double tempY = y;

    if (x < view.getSize().x / 2) {
        tempX = view.getSize().x / 2;
    }

    if (x > (mapWidth - view.getSize().x * 0.5)) {
        tempX = mapWidth - view.getSize().x * 0.5;
    }

    if (y < view.getSize().y / 2) {
        tempY = view.getSize().y / 2;
    }

    if (y >(mapHeight - view.getSize().y * 0.5)) {
        tempY = mapHeight - view.getSize().y * 0.5;
    }

    view.setCenter(tempX, tempY);
    return view;
}

Vector2i getMouseCoords(Vector2i mouse, Vector2u windowSize)
{
    mouse.x += view.getCenter().x - (view.getSize().x / 2);
    mouse.y += view.getCenter().y - (view.getSize().y / 2);
    return mouse;
}