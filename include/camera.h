#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>


class Camera {
private:
    float speed;
    glm::vec3 position;
    glm::vec3 forward;
    glm::vec3 up { 0, 1, 0 };

public:
    Camera(glm::vec3 position, glm::vec3 forward, float speed = 25) : 
        position { position },
        forward { forward },
        speed { speed } {}

    void moveLeft(float timeDifference) {
        position -= glm::normalize(glm::cross(forward, up)) * speed * timeDifference;
    }

    void moveRight(float timeDifference) {
        position += glm::normalize(glm::cross(forward, up)) * speed * timeDifference;
    }

    void moveForward(float timeDifference) {
        position += forward * speed * timeDifference;
    }

    void moveBackward(float timeDifference) {
        position -= forward * speed * timeDifference;
    }

    const glm::vec3 getPosition() {
        return position;
    }

    const glm::vec3 getForward() {
        return forward;
    }

    const glm::vec3 getUp() {
        return up;
    }

    const glm::mat4x4 lookThrough() {
        return glm::lookAt(
            getPosition(),
            getPosition() + getForward(),
            getUp()
        );
    }

};