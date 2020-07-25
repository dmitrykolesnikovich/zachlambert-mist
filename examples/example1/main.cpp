
#include <stdlib.h>
#include <stdio.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "scene/scene.h"
#include "window/window.h"
#include "window/fps_counter.h"
#include "window/clock.h"

void handle_input()
{
    const static float mouse_speed = 0.08f;
    double mx, my;
    glfwGetCursorPos(window, &mx, &my);
    // Reset mouse position for the next frame
    glfwSetCursorPos(window, WIDTH/2, HEIGHT/2);

    float pan_velocity = mouse_speed * float(WIDTH/2 - mx);
    float tilt_velocity = -mouse_speed * float(HEIGHT/2 - my);

    const static float speed = 5.0f;
    glm::vec3 camera_velocity;
    camera_velocity.x = 0;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera_velocity.x += speed;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera_velocity.x -= speed;
    }
    camera_velocity.z = 0;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera_velocity.z += speed;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera_velocity.z -= speed;
    }
    camera_velocity.y = 0;
    if (glfwGetKey(window, GLFW_KEY_SPACE)) {
        camera_velocity.y += speed;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)) {
        camera_velocity.y -= speed;
    }

    camera.set_velocity(camera_velocity);
    camera.set_pan_velocity(pan_velocity);
    camera.set_tilt_velocity(tilt_velocity);
}

int main()
{
    mist::Window window("Simple", 1024, 768);
    if (!window.initialise()) {
        return 1;
    }

    mist::Scene scene;

    entities.push_back(Entity(
        model_manager.get_model(texture_manager, "box/box.obj"),
        shader_manager.get_shader("default.vs", "default.fs")
    ));

    entities.push_back(Entity(
        model_manager.get_model(texture_manager, "sword/sword.obj"),
        shader_manager.get_shader("default.vs", "default.fs")
    ));
    entities[1].set_position(glm::vec3(4.0f, 0.0f, 0.0f));

    entities.push_back(Entity(
        model_manager.get_model(texture_manager, "golem/golem.obj"),
        shader_manager.get_shader("default.vs", "default.fs")
    ));
    entities[2].set_position(glm::vec3(-4.0f, 0.0f, 0.0f));

    entities.push_back(Entity(
        model_manager.get_model(texture_manager, "tree/tree.obj"),
        shader_manager.get_shader("default.vs", "default.fs")
    ));
    entities[3].set_position(glm::vec3(0.0f, 0.0f, 4.0f));

    light.set_position(glm::vec3(-5.0f, 5.0f, 5.0f));
    light.set_power(20.0f);
    light.set_color(glm::vec3(1.0f, 1.0f, 1.0f));

    mist::Clock clock;
    float dt;
    #ifndef NDEBUG
    mist::FpsCounter fps_counter;
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
