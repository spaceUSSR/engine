#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Camera
{
private:
    glm::vec3 m_cameraPos;
    glm::vec3 m_cameraFront;
    glm::vec3 m_cameraUp;

    float m_sensetivity;
    float m_speed;

    float m_yaw;
    float m_pitch;
public:
    Camera(float speed = 1.5f , float sensetivity = 1.7f);
public:
    ~Camera() {}
public:
    glm::mat4 look() const;
    inline glm::vec3 getPosition() const {return m_cameraPos; }
};

#endif //CAMERA_H
