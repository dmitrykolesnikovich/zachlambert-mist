#include "world.h"

World::World():
    model_manager("resources/models/"),
    texture_manager("resources/textures/"),
    shader_manager("resources/shaders/")
{
    const int size = 30;
    for (int i = -size; i <=size; i++) {
        for (int j = -size; j <=size; j++) {
            entities.push_back(Entity(
                model_manager.get_model(texture_manager, "box/box.obj"),
                shader_manager.get_shader("default.vs", "default.fs")
            ));
            float dist = hypot(2*i, 2*j);
            glm::vec3 pos(2.0f*i, 0, 2.0f*j);
            entities.rbegin()->set_position(pos);
            entities.rbegin()->set_orientation(glm::rotate(
                glm::radians(-15.0f)*dist,
                glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), pos))
            ));
        }
    }
    light.set_position(glm::vec3(0.0f, float(size), 0.0f));
    light.set_power(2000.0f);
    light.set_color(glm::vec3(1.0f, 1.0f, 1.0f));
}

void World::handle_input(GLFWwindow *window, const int WIDTH, const int HEIGHT)
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

void World::update(float dt)
{
    camera.update(dt);
    for(std::vector<Entity>::iterator it = entities.begin();
        it != entities.end();
        it++)
    {
        // it->update(dt);
    }

}

void World::render()
{
    for(std::vector<Entity>::iterator it = entities.begin();
        it != entities.end();
        it++)
    {
        it->render(camera, light);
    }
}
