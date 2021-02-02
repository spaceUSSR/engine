#include "events.h"
#include "camera.h"
#include "window.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <string.h>

float Events::m_lastXpos{0.0f};
float Events::m_lastYpos{0.0f};

bool* Events::m_key;
float Events::m_lastFrame = 0;
void Events::initialize()
{
	m_key = new bool[1024];
	memset(m_key, false, sizeof(bool)*1024);
}

void Events::finalize()
{
	delete [] m_key;
}

void Events::cursorPosCallBack(GLFWwindow *window, double xpos, double ypos)
{
	static bool first = true;
	if(first)
	{
		xpos = 0.0f;
		ypos = 0.0f;
		first = false;
	}

	(void)window;
	float xOffset = xpos - m_lastXpos;
	float yOffset = ypos - m_lastYpos;

	m_lastXpos = xpos;
	m_lastYpos = ypos;

	Camera::m_yaw += xOffset * Camera::m_sensetivity;
	Camera::m_pitch += yOffset * Camera::m_sensetivity * (-1.0f);

	if(Camera::m_pitch > 89.0f) {
		Camera::m_pitch = 89.0f;
	} else if(Camera::m_pitch < -89.0f) {
		Camera::m_pitch = -89.0f;
	}


	glm::vec3 direction;
	direction.x = cos(glm::radians(Camera::m_yaw)) * cos(glm::radians(Camera::m_pitch));
	direction.y = sin(glm::radians(Camera::m_pitch));
	direction.z = sin(glm::radians(Camera::m_yaw)) * cos(glm::radians(Camera::m_pitch)); ;
	Camera::m_cameraFront = glm::normalize(direction);
}

void Events::keyCallBack(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	(void)window;
	(void)scancode;
	(void)mods;
	if(action == GLFW_PRESS) {
		m_key[key] = true;
	} else if(action == GLFW_RELEASE){
		m_key[key] = false;
	}
}

void Events::pollEvents()
{
	float curentFrame = glfwGetTime();
	float delta = curentFrame - m_lastFrame;
	m_lastFrame = curentFrame;

	/* move camera */
	if(m_key[GLFW_KEY_W]) {
		Camera::m_cameraPos+= Camera::m_cameraFront * Camera::m_speed * delta;
	}
	if(m_key[GLFW_KEY_S]) {
		Camera::m_cameraPos-= Camera::m_cameraFront * Camera::m_speed * delta;
	}
	if(m_key[GLFW_KEY_A]) {
		Camera::m_cameraPos-= glm::normalize(glm::cross(Camera::m_cameraFront, Camera::m_cameraUp)) * Camera::m_speed * delta;
	}
	if(m_key[GLFW_KEY_D]) {
		Camera::m_cameraPos+= glm::normalize(glm::cross(Camera::m_cameraFront, Camera::m_cameraUp)) * Camera::m_speed * delta;
	}
	if(m_key[GLFW_KEY_ESCAPE]) {
		glfwSetWindowShouldClose(Window::m_window, true);
	}
	glfwPollEvents();
}
