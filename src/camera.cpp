#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

float Camera::m_speed{1.5};
float Camera::m_sensetivity{0.07};
float Camera::m_yaw{-90.0f};
float Camera::m_pitch{0.0f};

glm::vec3 Camera::m_cameraPos(0.0f, 0.0f, 0.0f);
glm::vec3 Camera::m_cameraFront(0.0f, 0.0f, -1.0f);
glm::vec3 Camera::m_cameraUp(0.0f, 1.0f, 0.0f);

glm::mat4 Camera::look()
{
	return glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);
}

glm::vec3 Camera::position()
{
	return m_cameraPos;
}


