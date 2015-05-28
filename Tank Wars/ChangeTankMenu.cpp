#include "ChangeTankMenu.h"


ChangeTankMenu::ChangeTankMenu(int nation, Player &player, Texture &texGUI) :
GameObject(player.getPos(), texGUI, IntRect(0, 0, 160, 100))
{
    position = player.getPos();

    const Vector2f texSize = Vector2f(160, 100);
    const Vector2f arrowSize = Vector2f(15, 100);

    if (nation == GERMANY) {
        texture.loadFromFile("images\\tiles\\ussr.png");
        texTank1.loadFromFile("images\\tiles\\T-46.png");
        texTank2.loadFromFile("images\\tiles\\T-34.png");
        texTank3.loadFromFile("images\\tiles\\KV1.png");
        texTank4.loadFromFile("images\\tiles\\IS.png");
        texTank5.loadFromFile("images\\tiles\\IS-3.png");

        tanks.push_back(new TankTile(&texTank1, 1, ussrT46));
        tanks.push_back(new TankTile(&texTank2, 2, ussrT34));
        tanks.push_back(new TankTile(&texTank3, 3, ussrKV1));
        tanks.push_back(new TankTile(&texTank4, 4, ussrIS));
        tanks.push_back(new TankTile(&texTank5, 5, ussrIS3));

    } else {
        texture.loadFromFile("images\\tiles\\germany.png");
        texTank1.loadFromFile("images\\tiles\\PZ1C.png");
        texTank2.loadFromFile("images\\tiles\\PZIV.png");
        texTank3.loadFromFile("images\\tiles\\TigerI.png");
        texTank4.loadFromFile("images\\tiles\\TigerII.png");
        texTank5.loadFromFile("images\\tiles\\Maus.png");

        tanks.push_back(new TankTile(&texTank1, 1, germanyPz1C));
        tanks.push_back(new TankTile(&texTank2, 2, germanyPZIV));
        tanks.push_back(new TankTile(&texTank3, 3, germanyTiger1));
        tanks.push_back(new TankTile(&texTank4, 4, germanyTiger2));
        tanks.push_back(new TankTile(&texTank5, 5, germanyMaus));
    }

    arrowNext.setTexture(texGUI);
    arrowNext.setTextureRect(IntRect(10, 40, 15, 100));
    arrowPrev.setTexture(texGUI);
    arrowPrev.setTextureRect(IntRect(25, 40, -15, 100));

    playerLevel = player.getLevel();

    sprite.setTexture(texture);
    sprite.setOrigin(80, 50);
    tank.setOrigin(80, 50);
    arrowNext.setOrigin(7.5, 50);
    arrowPrev.setOrigin(7.5, 50);


    sprite.setPosition(position);
    tank.setPosition(position);
    arrowPrev.setPosition(position.x - texSize.x / 2, position.y);
    arrowNext.setPosition(position.x + texSize.x / 2, position.y);

    mouse = new MouseCursor(Vector2f(0, 0), texGUI, IntRect(30, 0, 20, 20));
    mousePoint.setTextureRect(IntRect(0, 0, 1, 1));
}


bool ChangeTankMenu::run(Texture &texGUI, RenderWindow &window, Player &player)
{
    Vector2i mousePos;

    Event event;

    bool lifeOfPoint = true;

    int changeTank;

    std::list<TankTile*>::iterator thisTank;
    for (thisTank = tanks.begin(); thisTank != tanks.end(); thisTank++) {
        if ((*thisTank)->level == playerLevel) {
            break;
        }
    }

    tank.setTexture(*((*thisTank)->tex));

    while (true) {
        lifeOfPoint = true;

        mousePos = getMouseCoords(Mouse::getPosition(window), window.getSize());
        (*mouse).update((Vector2f)mousePos);
        mousePoint.setPosition((Vector2f)mousePos);

        while (window.pollEvent(event)) {
            // Если нажата стрелка влево
            if ((mousePoint.getGlobalBounds().intersects(
                arrowPrev.getGlobalBounds()) &&
                event.type == Event::MouseButtonPressed &&
                event.key.code == Mouse::Left) ||
                (event.type == Event::KeyPressed &&
                event.key.code == Keyboard::A)) {

                if (*thisTank != tanks.front()) {
                    thisTank--;
                    Texture* tex = (*thisTank)->tex;
                    tank.setTexture(*tex);
                }
            }

            // Если нажата стрелка вправо
            if ((mousePoint.getGlobalBounds().intersects(
                arrowNext.getGlobalBounds()) &&
                event.type == Event::MouseButtonPressed &&
                event.key.code == Mouse::Left) ||
                (event.type == Event::KeyPressed &&
                event.key.code == Keyboard::D)) {

                if (*thisTank != tanks.back()) {
                    thisTank++;
                    Texture* tex = (*thisTank)->tex;
                    tank.setTexture(*tex);
                }
            }

            // Если выбран танк и нажата ЛКМ, то создаём нового игрока
            if ((mousePoint.getGlobalBounds().intersects(
                sprite.getGlobalBounds()) &&
                event.type == Event::MouseButtonPressed &&
                event.key.code == Mouse::Left) ||
                (event.type == Event::KeyPressed &&
                event.key.code == Keyboard::Return)) {

                Vector2f playerPos = player.getPos();

                Player *tempPlayer = new Player(playerPos,
                    (*thisTank)->characteristic);
                player = *tempPlayer;

                lifeOfPoint = false;
                return lifeOfPoint;
            }
        }

        draw(window);
    }
}


void ChangeTankMenu::draw(RenderWindow &window)
{
    window.clear();
    GameObject::draw(window);
    window.draw(tank);
    window.draw(arrowPrev);
    window.draw(arrowNext);
    (*mouse).draw(window);
    window.display();
}

TankTile::TankTile(Texture* tex, int level, TankCharacteristic characteristic)
{
    this->tex = tex;
    this->level = level;
    this->characteristic = characteristic;
}