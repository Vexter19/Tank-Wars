#include "ChangeTankMenu.h"


ChangeTankMenu::ChangeTankMenu(int nation, Player &player, Texture &texGUI) :
GameObject(player.getPos(), texGUI, IntRect(74, 54, 211, 200))
{
    position = player.getPos();

    const Vector2f texSize = Vector2f(160, 100);
    const Vector2f arrowSize = Vector2f(27, 100);

    if (nation == USSR) {
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
    arrowNext.setTextureRect(IntRect(10, 40, arrowSize.x, arrowSize.y));
    arrowPrev.setTexture(texGUI);
    arrowPrev.setTextureRect(IntRect(10 + arrowSize.x, 40, -arrowSize.x, arrowSize.y));

    playerLevel = player.getLevel();

    flag.setTexture(texture);
    flag.setOrigin(80, 50);
    tank.setOrigin(80, 50);
    arrowNext.setOrigin(14, 50);
    arrowPrev.setOrigin(14, 50);


    flag.setPosition(position);
    tank.setPosition(position);
    arrowPrev.setPosition(position.x - texSize.x / 2 - arrowSize.x / 2 + 3, position.y - 1);
    arrowNext.setPosition(position.x + texSize.x / 2 + arrowSize.x / 2 - 3, position.y - 1);

    mouse = new MouseCursor(Vector2f(0, 0), texGUI, IntRect(30, 0, 20, 20));
    mousePoint.setTextureRect(IntRect(0, 0, 1, 1));

    sprite.setPosition(position.x, position.y + texSize.y / 2 - 4);

    font.loadFromFile(MAIN_FONT);
    level.setPosition(position.x - texSize.x / 2 + 10,
        position.y - texSize.y / 2 + 10);
    name.setPosition(position.x + texSize.x / 2 - 50,
        position.y + texSize.y / 2 - 25);
    hp.setPosition(position.x - texSize.x / 2 - 10,
        position.y + texSize.y / 2 + 10);
    damage.setPosition(position.x - texSize.x / 2 - 10,
        position.y + texSize.y / 2 + 30);
    recharging.setPosition(position.x - texSize.x / 2 - 10,
        position.y + texSize.y / 2 + 50);
    speed.setPosition(position.x - texSize.x / 2 - 10,
        position.y + texSize.y / 2 + 70);

    level.setFont(font);
    name.setFont(font);
    hp.setFont(font);
    damage.setFont(font);
    speed.setFont(font);
    recharging.setFont(font);

    level.setCharacterSize(16);
    name.setCharacterSize(16);
    hp.setCharacterSize(16);
    damage.setCharacterSize(16);
    speed.setCharacterSize(16);
    recharging.setCharacterSize(16);

    damageHead = L"Максимальный урон: ";
    hpHead = L"Очки прочности: ";
    speedHead = L"Макс. скорость: ";
    rechargingHead = L"Время перезарядки: ";
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

        while (window.pollEvent(event)) {
            // Если нажата стрелка влево
            if ((event.type == Event::KeyPressed &&
                event.key.code == Keyboard::A)) {

                if (*thisTank != tanks.front()) {
                    thisTank--;
                    Texture* tex = (*thisTank)->tex;
                    tank.setTexture(*tex);
                }
            }

            // Если нажата стрелка вправо
            if ((event.type == Event::KeyPressed &&
                event.key.code == Keyboard::D)) {

                if (*thisTank != tanks.back()) {
                    thisTank++;
                    Texture* tex = (*thisTank)->tex;
                    tank.setTexture(*tex);
                }
            }

            // Если выбран танк и нажата ЛКМ, то создаём нового игрока
            if (event.key.code == Keyboard::Return) {
                Vector2f playerPos = player.getPos();

                Player *tempPlayer = new Player(playerPos,
                    (*thisTank)->characteristic);
                player = *tempPlayer;

                lifeOfPoint = false;
                return lifeOfPoint;
            }

            level.setString(numToStr((*thisTank)->level));
            name.setString((*thisTank)->characteristic.name);
            hp.setString(hpHead + numToStr((*thisTank)->characteristic.health));
            damage.setString(damageHead + numToStr((*thisTank)->characteristic.damage));
            recharging.setString(rechargingHead + numToStr((*thisTank)->characteristic.rechargeTime) + L" с");
            speed.setString(speedHead + numToStr((*thisTank)->characteristic.maxSpeed) + L" км/ч");


            if (event.type == Event::Closed) {
                return false;
            }
        }

        draw(window);
    }
}


void ChangeTankMenu::draw(RenderWindow &window)
{
    //window.clear();
    GameObject::draw(window);
    window.draw(flag);
    window.draw(tank);
    window.draw(arrowPrev);
    window.draw(arrowNext);
    window.draw(level);
    window.draw(name);
    window.draw(hp);
    window.draw(damage);
    window.draw(recharging);
    window.draw(speed);
    (*mouse).draw(window);
    window.display();
}

TankTile::TankTile(Texture* tex, int level, TankCharacteristic characteristic)
{
    this->tex = tex;
    this->level = level;
    this->characteristic = characteristic;
}