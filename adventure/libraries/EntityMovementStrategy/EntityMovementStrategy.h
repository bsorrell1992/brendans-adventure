/*
 * Encapsulates the algorithm for entity movement
 */
#ifndef ENTITYMOVEMENTSTRATEGY_H
#define ENTITYMOVEMENTSTRATEGY_H

#include "Board.h"
#include "Entity.h"

class EntityMovementStrategy {
public:
    void move(Board* board, Entity* e) = 0;
};

#endif