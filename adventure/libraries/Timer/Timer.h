// Represents a timer
class Timer {
public:
    Timer(unsigned long delay);
    
    void startTimer();
    bool timeIsUp() const;

    // These methods are used by an entity with the speed boots
    void speedUp();
    void slowDown();
    
private:
    unsigned long _start;
    unsigned long _delay;
};