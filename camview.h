#pragma once
#include "vendor/glm/source/glm.hpp"
#include "vendor/glm/source/gtc/matrix_transform.hpp"
#include "vendor/glm/source/gtc/type_ptr.hpp"

class camera_view
{
public:
	glm::vec3 position;
	float pitch,yaw;

	camera_view(glm::vec3 pos, float pitchIn = 0.0f, float yawIn = -90.0f);

	glm::mat4 get_view_mat();

	void update();

	void mouse_handling(float moved_by_x,float moved_by_y);
	void keyboard_handling(unsigned char direction,const float DT);

private:
	glm::vec3 cam_right;
	glm::vec3 cam_up;
	glm::vec3 cam_front;

};