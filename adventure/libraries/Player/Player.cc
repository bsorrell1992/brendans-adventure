/*
    inline void Player::move(int dx, int dy) {
        Board* destBoard = currentBoard;
        int destX = x + dx;
        int destY = y + dy;

        // Determine which board the player is moving into
        if (destX < 0) {
            destBoard = destBoard->getLeft();
            destX = ARRAY_LENGTH - 1;
        } else if (destX >= ARRAY_LENGTH) {
            destBoard = destBoard->getRight();
            destX = 0;
        }
        if (destY < 0 && destBoard != nullptr) {
            destBoard = destBoard->getDown();
            destY = 0;
        } else if (destY >= ARRAY_LENGTH && destBoard != nullptr) {
            destBoard = destBoard->getTop();
            destY = ARRAY_LENGTH - 1;
        }

        if (destBoard != nullptr) {
            Entity* e = destBoard->board[destX][destY];
            String eType = e->getType();
            if (e == nullptr) {
            destBoard->board[destX][destY] = player;
            currentBoard->board[x][y] = nullptr;
            currentBoard = destBoard;
            x = destX;
            y = destY;
            } else if (eType == "guard") {
            if (!sword) {
                Guard* g = destBoard->board[destX][destY];
                if (g->timeToAttack()) g->attack();
            } else {
                addPoints(GUARD_POINTS);
                destBoard->board[destX][destY] = player;
                currentBoard->board[x][y] = nullptr;
                x = destX;
                y = destY;
                printKill(eType);
            }
            } else if (eType == "patrol") {
            if (!sword) {
                Patrol* p = destBoard->board[destX][destY];
                if (p->timeToAttack()) p->attack();
            } else {
                addPoints(PATROL_POINTS);
                destBoard->board[destX][destY] = player;
                currentBoard->board[x][y] = nullptr;
                x = destX;
                y = destY;
                printKill(eType);
            }
            } else if (eType == "sentry") {
            if (!sword) {
                Sentry* s = destBoard->board[destX][destY];
                if (s->timeToAttack()) s->attack();
            } else {
                addPoints(SENTRY_POINTS);
                destBoard->board[destX][destY] = player;
                currentBoard->board[x][y] = nullptr;
                x = destX;
                y = destY;
                printKill(eType);
            }
            } else if (eType == "boss") {
            if (!sword) {
                Boss* b = destBoard->board[destX][destY];
                if (b->timeToAttack()) b->attack();
            } else {
                addPoints(BOSS_POINTS);
                destBoard->board[destX][destY] = player;
                currentBoard->board[x][y] = nullptr;
                x = destX;
                y = destY;
                printKill(eType);
            }
            } else if (eType == "key") {
            grabKey();
            addPoints(ITEM_POINTS);
            destBoard->board[destX][destY] = player;
            currentBoard->board[x][y] = nullptr;
            x = destX;
            y = destY;
            Serial.println("Key!");
            } else if (eType == "sword") {
            grabSword();
            addPoints(ITEM_POINTS);
            destBoard->board[destX][destY] = player;
            currentBoard->board[x][y] = nullptr;
            x = destX;
            y = destY;
            Serial.println("Sword!");
            } else if (eType == "pickaxe") {
            grabPickaxe();
            addPoints(ITEM_POINTS);
            destBoard->board[destX][destY] = player;
            currentBoard->board[x][y] = nullptr;
            x = destX;
            y = destY;
            Serial.println("Pickaxe!");
            } else if (eType == "speedboots") {
            grabSpeedBoots();
            addPoints(ITEM_POINTS);
            destBoard->board[destX][destY] = player;
            currentBoard->board[x][y] = nullptr;
            x = destX;
            y = destY;
            Serial.println("Speed boots!");
            } else if (eType == "healthpotion") {
            grabHealthPotion();
            addPoints(ITEM_POINTS);
            destBoard->board[destX][destY] = player;
            currentBoard->board[x][y] = nullptr;
            x = destX;
            y = destY;
            Serial.println("Health potion!");
            } else if (eType == "armor") {
            grabArmor();
            addPoints(ITEM_POINTS);
            destBoard->board[destX][destY] = player;
            currentBoard->board[x][y] = nullptr;
            x = destX;
            y = destY;
            Serial.println("You grabbed the armor!");
            } else if (eType == "wall") {
            Wall* w = destBoard->board[destX][destY];
            if (w->isBreakable() && pickaxe) {
                addPoints(BREAKABLE_WALL_POINTS);
                destBoard->board[destX][destY] = player;
                currentBoard->board[x][y] = nullptr;
                x = destX;
                y = destY;
                Serial.print("You broke a wall!");
            } else {
                Serial.println("Oof!");
            }
            } else if (eType == "door") {
            if (key) {
                addPoints(DOOR_POINTS);

                // Remove all door objects from board
                for (int i = 0; i < ARRAY_LENGTH; ++i) {
                Entity* e = destBoard->board[i][destY];
                if (e != nullptr && e->getType() == "door") destBoard->board[i][destY] = nullptr;
                }

                destBoard->board[destX][destY] = player;
                currentBoard->board[x][y] = nullptr;
                x = destX;
                y = destY;
                Serial.print("You opened the door! Go claim your treasure!");
            } else {
                Serial.println("You need the key!");
            }
            } else if (eType == "treasure") {
            grabTreasure();
            addPoints(TREASURE_POINTS);
            destBoard->board[destX][destY] = player;
            currentBoard->board[x][y] = nullptr;
            x = destX;
            y = destY;

            // Fill edges of board with walls
            for (int i = 0; i < ARRAY_LENGTH; ++i) {
                destBoard->board[i][0] = &wall;
                destBoard->board[i][ARRAY_LENGTH - 1] = &wall;
            }
            for (int i = 1; i < ARRAY_LENGTH - 1; ++i) {
                destBoard->board[0][i] = &wall;
                destBoard->board[ARRAY_LENGTH - 1][i] = &wall;
            }

            Serial.print("Treasure! Your total is ");
            Serial.print(points);
            }
        }

        startMoveTimer();
    }
*/