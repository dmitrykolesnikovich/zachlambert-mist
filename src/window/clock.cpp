#include "window/clock.h"

#include <GLFW/glfw3.h>

namespace mist {

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

} // namespace mist
