#ifndef VIEW_H
#define VIEW_H
#include <SFML/Graphics.hpp>

#define WINDOW_WIDTH 1366
#define WINDOW_HEIGHT 768

using namespace sf;
extern View view;

extern const double mapWidth;
extern const double mapHeight;

View getViewCoords(double x, double y);

Vector2i getMouseCoords(Vector2i mouse, Vector2u windowSize);

#endif // !VIEW_H