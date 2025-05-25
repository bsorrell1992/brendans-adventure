/*
 * Encapsulates the algorithm for entity movement
 */
class EntityMovementStrategy {
public:
    void move(Board* board, Entity* e) = 0;
}