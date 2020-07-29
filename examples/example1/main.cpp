
#include <stdlib.h>
#include <stdio.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <GLFW/glfw3.h>

#include "scene/scene.h"
#include "window/window.h"
#include "window/fps_counter.h"
#include "window/clock.h"
#include "data/resource_config.h"
#include "render/renderer.h"

void handle_input(mist::Window &window, mist::Camera &camera)
{
    const static float mouse_speed = 0.08f;
    double mx, my;
    glfwGetCursorPos(window.get_window(), &mx, &my);
    // Reset mouse position for the next frame
    glfwSetCursorPos(window.get_window(), window.get_width()/2, window.get_height()/2);

    float pan_velocity = mouse_speed * float(window.get_width()/2 - mx);
    float tilt_velocity = -mouse_speed * float(window.get_height()/2 - my);

    const static float speed = 5.0f;
    glm::vec3 camera_velocity;
    camera_velocity.x = 0;
    if (glfwGetKey(window.get_window(), GLFW_KEY_W) == GLFW_PRESS) {
        camera_velocity.x += speed;
    }
    if (glfwGetKey(window.get_window(), GLFW_KEY_S) == GLFW_PRESS) {
        camera_velocity.x -= speed;
    }
    camera_velocity.z = 0;
    if (glfwGetKey(window.get_window(), GLFW_KEY_D) == GLFW_PRESS) {
        camera_velocity.z += speed;
    }
    if (glfwGetKey(window.get_window(), GLFW_KEY_A) == GLFW_PRESS) {
        camera_velocity.z -= speed;
    }
    camera_velocity.y = 0;
    if (glfwGetKey(window.get_window(), GLFW_KEY_SPACE)) {
        camera_velocity.y += speed;
    }
    if (glfwGetKey(window.get_window(), GLFW_KEY_LEFT_SHIFT)) {
        camera_velocity.y -= speed;
    }

    camera.set_velocity(camera_velocity);
    camera.set_pan_velocity(pan_velocity);
    camera.set_tilt_velocity(tilt_velocity);
}

int main()
{
    mist::Window window; // Sensible defaults
    if (!window.initialise()) {
        return 1;
    }

    mist::Renderer renderer;

    renderer.create_model_from_file("box", "models/box/box.obj");
    renderer.create_model_from_file("tree", "models/tree/tree.obj");

    mist::MaterialConfig matte_red;
    matte_red.set_diffuse_color(1, 0, 0);
    matte_red.set_specular_color(0.5f, 0.5f, 0.5f);

    mist::MeshConfig box_mesh;
    box_mesh.set_type(mist::MeshType::BOX);
    box_mesh.set_dimension("width", 1.5f);
    box_mesh.set_dimension("height", 0.5f);
    box_mesh.set_dimension("depth", 1.0f);
    box_mesh.set_material("matte red");

    renderer.create_model_from_config("red box", box_mesh, matte_red);

    mist::Entity box;
    box.set_model("box");
    box.set_position(glm::vec3(5.0f, 0.0f, 0.0f));

    mist::Entity tree;
    tree.set_model("tree");
    tree.set_position(glm::vec3(4.0f, 0.0f, 1.0f));

    mist::Scene scene;
    scene.add_entity("box", box);
    scene.add_entity("tree", tree);
    // scene.add_entity("red box", red_box);

    mist::Light light;
    light.set_position(glm::vec3(0.0f, 6.0f, -5.0f));
    light.set_color(1, 1, 1);
    light.set_power(100);
    scene.add_light("main light", light);

    mist::Camera &camera = scene.get_camera();
    camera.set_position(glm::vec3(0.0f, 3.0f, 0.0f));
    camera.set_tilt(0.6f);

    mist::Clock clock;

    renderer.initialise();

    renderer.add_entity(*scene.find_entity("box"));
    renderer.add_entity(*scene.find_entity("tree"));
    // renderer.add_entity(*scene.find_entity("red box"));

    while (window.is_running()) {
        float dt = clock.sample_dt();
        handle_input(window, scene.get_camera());
        scene.get_camera().update(dt);
        // update game logic
        // includes addition/insertion of entities, lights,
        // editing camera, changing entity models, etc.
        // On changing properties, a dirty flag is set within the object
        // telling the renderer to recompute any necessary information
        renderer.render(scene);

        window.update();
    }
    return 0;
}
