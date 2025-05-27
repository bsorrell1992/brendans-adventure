#include "BouncingLinearMovementStrategy.h"

/*
 * BouncingLinearMovementStrategy is assumed to be a friend of mover
 */
void BouncingLinearMovementStrategy::move(Board* board, Entity* mover) override {
    if (!mover->_moveTimer.timeIsUp()) return;

    if (!board->inBounds(mover->_position + mover->_offset)) mover->rebound();

    Point dest = mover->_position + mover->_offset;
    Entity* destOccupant = board->getEntityByPosition(dest);
    if (destOccupant != nullptr) {
        mover->attack(destOccupant);
        mover->rebound();
        dest = mover->_position + mover->_offset;
    }

    if (board->inBounds(toX, toY)) mover->_position = dest;

    mover->_moveTimer.startTimer();
}