#pragma once

#include "Core.h"

enum CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

namespace hz {
class Camera {
   private:
    // default camera values
    static constexpr float YAW = -90.f;
    static constexpr float PITCH = 0.0f;
    static constexpr float SPEED = 2.5f;
    static constexpr float SENSITIVITY = 0.1f;
    static constexpr float ZOOM = 45.0f;

    // camera attributes
    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;
    glm::vec3 m_world_up;

    // euler angles
    float m_yaw;
    float m_pitch;

   public:
    // camera options
    float movement_speed;
    float mouse_sensitivity;
    float zoom;

    // constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
           glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

    // constructor with scalar values
    Camera(float pos_x, float pos_y, float pos_z, float up_x, float up_y,
           float up_z, float yaw, float pitch);

    glm::mat4 get_view_matrix();
    void process_keyboard(CameraMovement direction, float delta_time);
    void process_mouse_movement(float x_offset, float y_offset, GLboolean constrainPitch = true);
    void process_mouse_scroll(float y_offset);

   private:
    void update_camera_vectors();
};
}  // namespace hz