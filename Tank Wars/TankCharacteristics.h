#include <SFML/Graphics.hpp>

using namespace sf;

struct TankCharacteristic
{
    std::string name; // �������� �����
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