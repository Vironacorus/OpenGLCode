#include "camview.h"
#include <iostream>

camera_view::camera_view(glm::vec3 pos, float pitchIn, float yawIn) : position(pos), yaw(yawIn), pitch(pitchIn), cam_front(glm::vec3(0.0f, 0.0f, -1.0f))
{
	update();
}
glm::mat4 camera_view::get_view_mat()
{
	return glm::lookAt(position, position + cam_front, cam_up);
}

void camera_view::update()
{
	cam_front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	cam_front.y = sin(glm::radians(pitch));
	cam_front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cam_front = glm::normalize(cam_front);
	cam_right = glm::normalize(glm::cross(cam_front, glm::vec3(0, 1, 0)));
	cam_up = glm::normalize(glm::cross(cam_right, cam_front));
}

void camera_view::mouse_handling(float moved_by_x, float moved_by_y)
{
    constexpr float sensitivity = 0.2f;
    yaw += moved_by_x*sensitivity;
    pitch += moved_by_y*sensitivity;

    if (pitch > 89.0f)
        pitch = 89.0f;
    else if (pitch < -89.0f)
        pitch = -89.0f;
}

void camera_view::keyboard_handling(unsigned char direction, const float DT)
{
        float velocity = 10.0f * DT;
        if (direction == 0)
            position += glm::vec3(cam_front.x,0,cam_front.z) * velocity;
        else if (direction == 1)
            position -= glm::vec3(cam_front.x, 0, cam_front.z) * velocity;
        else if (direction == 2)
            position -= glm::vec3(cam_right.x, 0, cam_right.z) * velocity;
        else if (direction == 3)
            position += glm::vec3(cam_right.x, 0, cam_right.z) * velocity;
}
