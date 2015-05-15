#include <SFML/Graphics.hpp>

using namespace sf;

struct TankCharacteristic
{
    std::string name; // Название танка
    std::string texturePath; // Путь к текстуре
    IntRect texRectBody; // Прямоугольник текстуры корпуса
    IntRect texRectTurrel; // Прямоугольник текстуры башни
    int turrelCenterX; // Абсцисса центра башни (относительно текстуры башни)
    int diffTankTurrel; // Расстояние между центром танка и
                        // центром оси вращения башни
    double maxSpeed; // Максимальная скорость танка, км/ч
    double speedOfRotation; // Скорость поворота вокруг оси, град/с 
    double speedTurrel; // Скорость вращения башни, град/с
    double rechargeTime; // Время перезарядки орудия, с
    int damage; // Урон по умолчанию
    int health; // Очки прочности по умолчанию
};


extern TankCharacteristic ussrT46;
extern TankCharacteristic ussrT34;
extern TankCharacteristic ussrKV1;
extern TankCharacteristic ussrIS;
extern TankCharacteristic ussrIS3;
extern TankCharacteristic germanyPz1C;
extern TankCharacteristic germanyPZIV;
extern TankCharacteristic germanyTiger1;
extern TankCharacteristic germanyTiger2;
extern TankCharacteristic germanyMaus;