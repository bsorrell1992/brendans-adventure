#include "EntityMemento.h"

template <typename T>
EntityMemento<T>::EntityMemento<T>(T& state) : _state(state) {}

template <typename T>
T& EntityMemento::getState() const {
    return _state;
}