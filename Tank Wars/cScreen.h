#ifndef CSCREEN_H
#define CSCREEN_H
#include "SFML/Graphics.hpp"

class cScreen
{
public:
    virtual int Run(sf::RenderWindow &window) = 0;
};

#endif // !CSCREEN_H