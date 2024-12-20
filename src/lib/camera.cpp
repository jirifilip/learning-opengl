#include <glm.hpp>
#include <gtc/matrix_transform.hpp>


#include "camera.h"


Camera::Camera(glm::vec3 position, glm::vec3 forward, float speed = 25) : 
        position { position },
        forward { forward },
        speed { speed } {}


void Camera::moveLeft(float timeDifference) {
    position -= glm::normalize(glm::cross(forward, up)) * speed * timeDifference;
}


void Camera::moveRight(float timeDifference) {
    position += glm::normalize(glm::cross(forward, up)) * speed * timeDifference;
}


void Camera::moveForward(float timeDifference) {
    position += forward * speed * timeDifference;
}


void Camera::moveBackward(float timeDifference) {
    position -= forward * speed * timeDifference;
}

void Camera::setForward(glm::vec3 forward) {
    this->forward = forward;
}


const glm::vec3 Camera::getPosition() {
    return position;
}


const glm::vec3 Camera::getForward() {
    return forward;
}


const glm::vec3 Camera::getUp() {
    return up;
}


const glm::mat4x4 Camera::lookThrough() {
    return glm::lookAt(
        getPosition(),
        getPosition() + getForward(),
        getUp()
    );
}
