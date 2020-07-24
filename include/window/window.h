#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

namespace window {

class Window {
public:
    Window(const std::string &name, unsigned int width, unsigned int height);
    bool initialise();
    unsigned int get_width() { return width; }
    unsigned int get_height() { return height; }
    GLFWwindow *get_window() { return window; }
private:
    const std::string &name;
    unsigned int width;
    unsigned int height;
    GLFWwindow *window;
};

} // namespace window

#endif
