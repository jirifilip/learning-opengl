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

    const glm::vec3 getPosition();

    const glm::vec3 getForward();

    const glm::vec3 getUp();

    const glm::mat4x4 lookThrough();

};