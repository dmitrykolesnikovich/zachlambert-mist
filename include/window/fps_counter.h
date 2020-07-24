#ifndef FPS_COUNTER_H
#define FPS_COUNTER_H

namespace window {

class FpsCounter {
public:
    FpsCounter();
    void update();
private:
    double last_logged_time;
    double current_time;
    int num_frames = 0;
};

} // namespace window

#endif
