#ifndef GRAPHICS_CAMERA_H
#define GRAPHICS_CAMERA_H

#include <glm/glm.hpp>

/* Represent the camera orientation with euler angles
 * The forward direction of the camera is
 *
 */

class Camera{
public:
    Camera(
        float fov_degrees = 45.0f,
        float aspect_ratio = 4.0f/3.0f);

    void update(float dt);

    const glm::mat4 &get_view() const { return view; }
    const glm::mat4 &get_projection() const { return projection; }

    void set_position(const glm::vec3 &position){
        this->position = position;
        update_position = true;
    }
    void set_velocity(const glm::vec3 &velocity){
        this->velocity = velocity;
    }
    void set_pan(float pan){
        this->pan = pan;
        update_directions = true;
    }
    void set_tilt(float tilt){
        this->tilt = tilt;
        update_directions = true;
    }
    void set_pan_velocity(float pan_velocity){
        this->pan_velocity = pan_velocity;
    }
    void set_tilt_velocity(float tilt_velocity){
        this->tilt_velocity = tilt_velocity;
    }
private:
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 forward, up, right;
    float pan, tilt, pan_velocity, tilt_velocity;
    glm::mat4 view;
    glm::mat4 projection;
    bool update_position, update_directions;
    const float TILT_LIMIT = glm::radians(85.0f);
};

#endif
