// Used to store entity state between loops
template <typename T>
class EntityMemento {
public:
    EntityMemento<T>(T& state);

private:
    T& getState() const;

    T _state;
};