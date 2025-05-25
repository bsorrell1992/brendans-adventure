#include "Board.h"
#include "Entity.h"
#include "EntityMovementStrategy.h"

/*
 * Implements the movement algorithm for entities which move in a straight line and bounce off of other entities
 */
class BouncingLinearMovementStrategy : public EntityMovementStrategy {
public:
    void move(Board* board, Entity* e) override;
}