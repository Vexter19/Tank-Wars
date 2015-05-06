#include "Enemy.h"


Enemy::Enemy(Vector2f pos, Texture *texDynObjs, Texture &tex, IntRect rect, IntRect rectTurrel,
    int turrelCenterX, int diffTankTurrel, double maxSpeed,
    double speedOfRotation, double speedTurrel, int health,
    double rechargeTime, int damage, std::string name) :
    Tank(pos, tex, rect, rectTurrel, turrelCenterX, diffTankTurrel,
    maxSpeed, speedOfRotation, speedTurrel, rechargeTime, damage, name, health)
{
    this->texDynamicObjects = texDynObjs;
    this->health = 200;
    direction = 0;
    rotation = 0;
    IntRect temp = this->sprite.getTextureRect();
    bigSprite.setOrigin(temp.width / 2, temp.height / 2);
    temp.width *= 3;
    
    travelled = 0;

    // ������. ���������� �������� ����������� �����
    bigSprite.setTexture(*texDynObjs);
    bigSprite.setTextureRect(temp);
    bigSprite.setColor(Color::Red);
}

void Enemy::update(double time, Tank &player, std::list<Bullet*> &bullets,
    std::list<GameObject*> &objects, std::list<Animation*> &anims)
{
    Vector2f vecPlayer; // ������ ����� ������ � �������
    vecPlayer.x = player.getPos().x - position.x;
    vecPlayer.y = player.getPos().y - position.y;
    if (vectorLength(vecPlayer) < VISIBILITY) {
        alert = false;
    } else {
        alert = false;
    }
    if (alert == false) { // ���� ���� �� ����� ������
        // ������������ �� ��������� ����
        // ���� �� �������� ������ ����������
        travelled += 1 / 1000;
        if (travelled < 10) {
            for (std::list<GameObject*>::iterator it = objects.begin();
                it != objects.end(); ++it) {
                GameObject *obj = *it;
                if (Collision::BoundingBoxTest(bigSprite, obj->getSprite()) ||
                    isOutOfMap()) {
                    // ���� �� ���� ���� ������
                    srand(time);
                    int randDir;
                    
                    if ((rand() % 2) == 0) {
                        randDir = -1;
                        prevRandDir = randDir;
                    } else {
                        randDir = 1;
                        prevRandDir = randDir;
                    }
                    if (prevRandDir == randDir) {
                        randDir *= -1;
                    }
                    double backupAngle = bigSprite.getRotation();
                    bigSprite.setRotation(backupAngle + randDir * TRY_ROTATE_ANGLE);

                    if (Collision::BoundingBoxTest(bigSprite, obj->getSprite())
                        == false && !isOutOfMap()) {
                        rotation = 1;
                        break;
                    } else {
                        bigSprite.setRotation(backupAngle - randDir * TRY_ROTATE_ANGLE);
                        if (Collision::BoundingBoxTest(bigSprite, obj->getSprite())
                            == false && !isOutOfMap()) {
                            rotation = -1;
                            break;
                        }
                    }
                    //bigSprite.setRotation(backupAngle);
                } else {
                    direction = 1;
                    rotation = 0;
                }
                if (isOutOfMap()) {
                    direction = -1;
                }
            }
            // ���� �����
            // ���� ������� �����������
            // ��������� ��� �� ����������� �� ����������� +45 ��������
            // ���� ���, ������������ ������ ���� ���� �� ����� ��������
            // ���� ����, �� ��������� ����������� -45
            // ������������ �����
            // ���� ����������� ���, ������ ���� �����
            // ���� ������� ���� �����
            //  ������� ������������
        }
        // ����� �������� n ������
        // ��������������� �� ��������� ������
        // ������� ������
        // ���������� ��������
    } else { // ���� ���� ����� ������
        // ��������� 
        // ������������ ����� �� ������
        // ������������ ������
        // ���� ��� ����������� �� ��������
        // ���� ����
            // ������� �����������
    }

    Tank::update(time, direction, rotation, objects, bullets, anims);
    GameObject *objPlayer = &player;
    if (checkCollision(objPlayer) == true) {
        Tank::update(time, -direction, -rotation, objects, bullets, anims);
    }

    bigSprite.setPosition(position);
    bigSprite.setRotation(angle);
}

bool Enemy::isOutOfMap()
{
    Vector2f point;
    point.x = bigSprite.getPosition().x + bigSprite.getTextureRect().width *
        cos(bigSprite.getRotation() * PI / 180);
    point.y = bigSprite.getPosition().y + bigSprite.getTextureRect().width *
        sin(bigSprite.getRotation() * PI / 180);
    if (point.x > mapWidth || point.x < 0 ||
        point.y > mapHeight || point.y < 0) {
        return true;
    } else {
        return false;
    }
}