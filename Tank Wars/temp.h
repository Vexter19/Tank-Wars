if (alert == false) {
    // Спокойное поведение врага
    direction = 1;
    //Tank::update(time, direction, rotation, objects, bullets, anims);
} else {
    // Враг видит игрока

    if (player.isAlive()) {
        direction = -0.1;

        double scalar;

        // Поворот корпуса лбом к игроку
        scalar = scalarProd(normalizeVector(vecPlayer),
            Vector2f(cos(angle * PI / 180), sin(angle * PI / 180)));

        rotation = rotate(player.getPos(), angle);

        if (scalar > COS_30) {
            rotation = 0;
        }

        // Поворот башни на игрока
        rotateTurrel((Vector2i)player.getPos());

        /* Если угол между вектором направления башни врага
        и игроком меньше 10 градусов, то можно стрелять */
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
            // Если на пути есть объект
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