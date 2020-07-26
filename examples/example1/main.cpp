
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
#include "data/resource_config.h"
#include "render/renderer.h"

/*
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
*/

int main()
{
    mist::Window window; // Sensible defaults
    if (!window.initialise()) {
        return 1;
    }

    mist::Resources resources;

    resources.create_model_from_file("box", "models/box/box.obj");

    mist::MaterialConfig matte_red;
    matte_red.set_diffuse_color(1, 0, 0);
    matte_red.set_specular_color(0.5f, 0.5f, 0.5f);
    resources.create_material_from_config("matte red", matte_red);

    mist::ModelConfig my_sphere_config;
    my_sphere_config.set_type(mist::ModelType::SPHERE);
    my_sphere_config.set_dimension("radius", 2);
    my_sphere_config.set_material("matte red");
    resources.create_model_from_config("my_sphere", my_sphere_config);

    mist::Entity box;
    box.set_model("box");
    box.set_orientation(glm::rotate(glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f)));

    mist::Entity sphere;
    sphere.set_model("my_sphere");

    mist::Scene scene;
    scene.add_entity("box", box);
    scene.add_entity("sphere", sphere);

    mist::Light light;
    light.set_position(glm::vec3(1.0f, 6.0f, 1.0f));
    light.set_color(1, 1, 1);
    light.set_power(10);
    scene.add_light("main light", light);

    mist::Camera &camera = scene.get_camera();
    camera.set_position(glm::vec3(0.0f, 0.0f, 5.0f));

    mist::Renderer renderer;

    mist::Clock clock;

    while (window.is_running()) {
        float dt = clock.sample_dt();
        // update game logic
        // includes addition/insertion of entities, lights,
        // editing camera, changing entity models, etc.
        // On changing properties, a dirty flag is set within the object
        // telling the renderer to recompute any necessary information
        renderer.render(scene, resources);
    }
    return 0;
}
