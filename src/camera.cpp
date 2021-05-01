#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Camera::Camera(float speed, float sensetivity) :
    m_cameraPos(0.0f, 0.0f, 0.0f),
    m_cameraFront(0.0f, 0.0f, -1.0f),
    m_cameraUp(0.0f, 1.0f, 0.0f),
    m_sensetivity(sensetivity), m_speed(speed),
    m_yaw(-90.f), m_pitch(0.0f) {}

glm::mat4 Camera::look() const
{
	return glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);
}
