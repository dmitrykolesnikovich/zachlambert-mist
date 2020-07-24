#include "window/clock.h"

#include <GLFW/glfw3.h>

namespace window {

Clock::Clock()
{
    prev_time = glfwGetTime();
}

float Clock::sample_dt()
{
    current_time = glfwGetTime();
    dt = current_time - prev_time;
    prev_time = current_time;
    return dt;
}

} // namespace window
