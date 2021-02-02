#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
class Camera
{
public:
	static glm::mat4 look();
	static glm::vec3 position();

private:
	static glm::vec3 m_cameraPos;
	static glm::vec3 m_cameraFront;
	static glm::vec3 m_cameraUp;
	static float m_sensetivity;
	static float m_speed;

	static float m_yaw;
	static float m_pitch;

	friend class Events;
};

#endif //CAMERA_H
