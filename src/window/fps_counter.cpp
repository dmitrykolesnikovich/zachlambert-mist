#include "window/fps_counter.h"

#include <stdio.h>
#include <GLFW/glfw3.h>

namespace window {

FpsCounter::FpsCounter()
{
    last_logged_time = glfwGetTime();
}

void FpsCounter::update()
{
    current_time = glfwGetTime();
    num_frames++;
    if (current_time - last_logged_time > 1.0) {
        printf("%f ms/frame (%d FPS)\n", 1000.0/double(num_frames), num_frames);
        num_frames = 0;
        last_logged_time = current_time;
    }
}

} // namespace window
