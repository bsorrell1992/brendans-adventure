class Wall : public Entity {
public:
    Wall(bool isBreakable);
    Wall();
    ~Wall() {};
    Entity::MoveResult receiveMove(Entity* e) override;

private:
    bool _isBreakable;
}