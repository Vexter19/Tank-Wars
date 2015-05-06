if (alert == false) {
    // ��������� ��������� �����
    direction = 1;
    //Tank::update(time, direction, rotation, objects, bullets, anims);
} else {
    // ���� ����� ������

    if (player.isAlive()) {
        direction = -0.1;

        double scalar;

        // ������� ������� ���� � ������
        scalar = scalarProd(normalizeVector(vecPlayer),
            Vector2f(cos(angle * PI / 180), sin(angle * PI / 180)));

        rotation = rotate(player.getPos(), angle);

        if (scalar > COS_30) {
            rotation = 0;
        }

        // ������� ����� �� ������
        rotateTurrel((Vector2i)player.getPos());

        /* ���� ���� ����� �������� ����������� ����� �����
        � ������� ������ 10 ��������, �� ����� �������� */
        scalar = scalarProd(normalizeVector(vecPlayer),
            Vector2f(cos(dirTurrel * PI / 180), sin(dirTurrel * PI / 180)));

        if (scalar > COS_10) {
            fire(bullets, *texDynamicObjects);
        }
    }

    for (std::list<GameObject*>::iterator it = objects.begin();
        it != objects.end(); ++it) {
        GameObject *obj = *it;
        if (Collision::BoundingBoxTest(bigSprite, obj->getSprite())) {
            // ���� �� ���� ���� ������
            double backupAngle = bigSprite.getRotation();
            bigSprite.setRotation(backupAngle + TRY_ROTATE_ANGLE);

            if (Collision::BoundingBoxTest(bigSprite, obj->getSprite())) {
                //bigSprite.setRotation(backupAngle - TRY_ROTATE_ANGLE);
                rotation = -1;
            } else {
                rotation = 1;
            }
        } else {
            direction = 1;
            rotation = 0;
        }
    }
}