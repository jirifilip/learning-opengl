#pragma once

#include <glm.hpp>


class Camera {
private:
    glm::vec3 position;
    glm::vec3 forward;
    float speed;
    glm::vec3 up { 0, 1, 0 };

public:
    Camera(glm::vec3 position, glm::vec3 forward, float speed);

    void moveLeft(float timeDifference);

    void moveRight(float timeDifference);

    void moveForward(float timeDifference);

    void moveBackward(float timeDifference);

    void moveUp(float timeDifference); 

    void setForward(glm::vec3 forward);

    const glm::mat4x4 lookThrough();
};