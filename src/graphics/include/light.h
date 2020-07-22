#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>

class Light {
public:
    Light() {}
    void set_position(const glm::vec3 &position){
        this->position = position;
    }
    const glm::vec3 &get_position() const { return position; }
    void set_power(float power){
        this->power = power;
    }
    float get_power() const { return power; }
    void set_color(const glm::vec3 &color){
        this->color = color;
    }
    const glm::vec3 &get_color() const { return color; }
private:
    glm::vec3 position = glm::vec3(0.0f, 10.0f, 0.0f);
    float power = 5.0f;
    glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
};

#endif
