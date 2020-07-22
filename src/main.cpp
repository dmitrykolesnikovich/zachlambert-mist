
#include <stdlib.h>
#include <stdio.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "load_resources.h"
#include "world.h"
#include "resources.h"
#include "window.h"
#include "fps_counter.h"
#include "clock.h"

int main()
{
    Window window("Simple", 1024, 768);
    if (!window.initialise()) {
        return 1;
    }

    Resources resources;
    resources.models.push_back(Model(
        "resources/models/chimney/chimney.obj",
        "resources/textures/"
    ));
    resources.models.push_back(Model(
        "resources/models/random/random.obj",
        "resources/textures/"
    ));
    resources.models.push_back(Model(
        "resources/models/box/box.obj",
        "resources/textures/box/"
    ));
    resources.shaders.push_back(Shader(
        "resources/shaders/default.vs",
        "resources/shaders/default.fs"
    ));

    World world(resources);

    Clock clock;
    float dt;
    #ifndef NDEBUG
    FpsCounter fps_counter;
    #endif

    do {
        #ifndef NDEBUG
        fps_counter.update();
        #endif
        dt = clock.sample_dt();

        glClearColor(0.3f, 0.3f, 0.3f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        world.handle_input(window.get_window(), window.get_width(), window.get_height());
        world.update(dt);
        world.render();

        glfwSwapBuffers(window.get_window());
        glfwPollEvents();
    } while (
        glfwGetKey(window.get_window(), GLFW_KEY_ESCAPE) != GLFW_PRESS
        && glfwWindowShouldClose(window.get_window()) == 0
    );

    return 0;
}
