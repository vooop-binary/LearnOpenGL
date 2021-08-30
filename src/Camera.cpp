#include "Camera.h"

namespace hz {
// constructor with vectors
Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : m_front(glm::vec3(0.0f, 0.0f, -1.0f)), movement_speed(SPEED), mouse_sensitivity(SENSITIVITY), zoom(ZOOM) {
    m_position = position;
    m_world_up = up;
    m_yaw = yaw;
    m_pitch = pitch;
    update_camera_vectors();
}

// constructor with scalar values
Camera::Camera(float pos_x, float pos_y, float pos_z, float up_x, float up_y,
               float up_z, float yaw, float pitch)
    : m_front(glm::vec3(0.0f, 0.0f, -1.0f)), movement_speed(SPEED), mouse_sensitivity(SENSITIVITY), zoom(ZOOM) {
    m_position = glm::vec3(pos_x, pos_y, pos_z);
    m_world_up = glm::vec3(up_x, up_y, up_z);
    m_yaw = yaw;
    m_pitch = pitch;
    update_camera_vectors();
}

glm::mat4 Camera::get_view_matrix() {
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

void Camera::process_keyboard(CameraMovement direction, float delta_time) {
    float velocity = movement_speed * delta_time;

    if (direction == FORWARD) {
        m_position += m_front * velocity;
    }
    if (direction == BACKWARD) {
        m_position -= m_front * velocity;
    }
    if (direction == RIGHT) {
        m_position += m_right * velocity;
    }

    if (direction == LEFT) {
        m_position -= m_right * velocity;
    }
}

void Camera::process_mouse_movement(float x_offset, float y_offset, GLboolean constrain_pitch) {
    x_offset *= mouse_sensitivity;
    y_offset *= mouse_sensitivity;

    m_yaw += x_offset;
    m_pitch += y_offset;

    if (constrain_pitch) {
        if (m_pitch > 89.0f)
            m_pitch = 89.0f;
        if (m_pitch < -89.0f)
            m_pitch = -89.0f;
    }

    update_camera_vectors();
}

void Camera::process_mouse_scroll(float y_offset) {
    zoom -= y_offset;

    if (zoom < 1.0f)
        zoom = 1.0f;
    if (zoom > 45.0f)
        zoom = 45.0f;
}

void Camera::update_camera_vectors() {
    // calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y = sin(glm::radians(m_pitch));
    front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_front = glm::normalize(front);
    // also re-calculate the Right and Up vector
    m_right = glm::normalize(glm::cross(m_front, m_world_up));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    m_up = glm::normalize(glm::cross(m_right, m_front));
}
}  // namespace hz