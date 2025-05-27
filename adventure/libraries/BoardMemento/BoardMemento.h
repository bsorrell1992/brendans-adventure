/*
 * Used to store entity state between loops
 */
class BoardMemento {
public:
    BoardMemento(Board* state);

private:
    T& getState() const;

    T _state;
};