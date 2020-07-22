#ifndef CLOCK_H
#define CLOCK_H

class Clock {
public:
    Clock();
    float sample_dt();
private:
    float dt, prev_time, current_time;
};

#endif
