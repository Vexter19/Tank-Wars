#ifndef TANKCHARACTERISTICS_H
#define TANKCHARACTERISTICS_H

#include <SFML/Graphics.hpp>


using namespace sf;

struct TankCharacteristic
{
    std::wstring name; // �������� �����
    int level;
    std::string texturePath; // ���� � ��������
    IntRect texRectBody; // ������������� �������� �������
    IntRect texRectTurrel; // ������������� �������� �����
    int turrelCenterX; // �������� ������ ����� (������������ �������� �����)
    int diffTankTurrel; // ���������� ����� ������� ����� �
    // ������� ��� �������� �����
    double maxSpeed; // ������������ �������� �����, ��/�
    double speedOfRotation; // �������� �������� ������ ���, ����/� 
    double speedTurrel; // �������� �������� �����, ����/�
    double rechargeTime; // ����� ����������� ������, �
    int damage; // ���� �� ���������
    int health; // ���� ��������� �� ���������
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

#endif // !TANKCHARACTERISTICS_H