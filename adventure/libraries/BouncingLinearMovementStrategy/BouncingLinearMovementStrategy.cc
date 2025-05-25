#include "BouncingLinearMovementStrategy.h"

/*
 * BouncingLinearMovementStrategy is assumed to be a friend of mover
 */
void BouncingLinearMovementStrategy::move(Board* board, Entity* mover) override {
    if (!mover->_moveTimer.timeIsUp()) return;

    if (!board->inBounds(mover->_position.x + mover->_xOffset, mover->_position.y + mover->_yOffset)) rebound();

    int toX = mover->_position.x + mover->_xOffset;
    int toY = mover->_position.y + mover->_yOffset;
    Entity* destOccupant = board->getEntityByPosition(toX, toY);
    if (destOccupant != nullptr) {
        mover->attack(destOccupant);
        
        rebound();
        toX = mover->_position.x + mover->_xOffset;
        toY = mover->_position.y + mover->_yOffset;
    }

    if (board->inBounds(toX, toY)) {
        mover->_position.x = toX;
        mover->_position.y = toY;
    }

    mover->_moveTimer.startTimer();
}