#ifndef CLOCK_H
#define CLOCK_H

namespace window {

class Clock {
public:
    Clock();
    float sample_dt();
private:
    float dt, prev_time, current_time;
};

} // namespace window

#endif
