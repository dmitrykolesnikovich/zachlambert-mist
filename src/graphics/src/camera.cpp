#include "camera.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

Camera::Camera(
        float fov_degrees,
        float aspect_ratio):
    position(glm::vec3(0.0f, 0.0f, 0.0f)),
    velocity(glm::vec3(0.0f, 0.0f, 0.0f)),
    forward(glm::vec3(1.0f, 0.0f, 0.0f)),
    up(glm::vec3(0.0f, 1.0f, 0.0f)),
    right(glm::vec3(0.0f, 0.0f, 1.0f)),
    pan(0), tilt(0), pan_velocity(0), tilt_velocity(0),
    view(glm::mat4(1.0f)),
    projection(glm::perspective(
        glm::radians(fov_degrees), aspect_ratio, 0.1f, 100.0f)
    ),
    update_position(true), update_directions(true) {
}

void Camera::update(float dt)
{
    if (pan_velocity != 0) {
        pan += dt * pan_velocity;
        update_directions = true;
    }
    if (pan_velocity != 0) {
        tilt += dt * tilt_velocity;
        if (tilt > TILT_LIMIT) {
            tilt = TILT_LIMIT;
        } else if (tilt < -TILT_LIMIT) {
            tilt = -TILT_LIMIT;
        }
        update_directions = true;
    }
    if (update_directions) {
        forward = glm::vec3(
            cos(pan) * cos(tilt),
            -sin(tilt),
            -sin(pan) * cos(tilt)
        );
        up = glm::vec3(
            cos(pan) * sin(tilt),
            cos(tilt),
            -sin(pan) * sin(tilt)
        );
        right = glm::cross(forward, up);
    }
    if (glm::length(velocity) > 0) {
        position += dt * (
            velocity[0] * forward
            + velocity[1] * up
            + velocity[2] * right
        );
        update_position = true;
    }
    if (update_position || update_directions) {
        view = glm::lookAt(position, position + forward, up);
    }
}
