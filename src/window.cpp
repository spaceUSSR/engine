#include "window.h"
#include "events.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

GLFWwindow* Window::m_window = 0;
int Window::m_height = 480;
int Window::m_width = 640;

extern float yaw;
extern float pitch;

float lastX = 400, lastY = 300;

int Window::getHeight()
{
    return m_height;
}

void Window::setHeight(int height)
{
    m_height = height;
}

int Window::getWidth()
{
    return m_width;
}

void Window::setWidth(int width)
{
    m_width = width;
}

int Window::initialize(int w, int h, const char* title)
{
    
    if (!glfwInit())
    {
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    m_window = glfwCreateWindow(w, h, title, nullptr, nullptr);
    if (!m_window)
    {
        glfwTerminate();
        return 2;
    }

    glfwSetWindowSizeCallback(m_window, glfwWindowSizeCallBack);
	glfwSetKeyCallback(m_window, Events::keyCallBack);
	glfwSetCursorPosCallback(m_window, Events::cursorPosCallBack);
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    /* Make the window's context current */
    glfwMakeContextCurrent(m_window);

    if(!gladLoadGL())
    {
        glfwDestroyWindow(m_window);
        glfwTerminate();
        return 3;
    }
	Events::initialize();
    return 0;
}

bool Window::isSouldClose()
{
    return glfwWindowShouldClose(m_window);
}

void Window::swapBuffers()
{
    glfwSwapBuffers(m_window);
}

void Window::clearColor(float r, float g, float b, float a)
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

int Window::getKey(int key)
{
    return glfwGetKey(m_window, key);
}

int Window::finalize()
{
	Events::finalize();
    glfwDestroyWindow(m_window);
    glfwTerminate();
    return 0;
}

void Window::glfwWindowSizeCallBack(GLFWwindow *pWindow, int width, int height)
{
    (void)pWindow;
    m_height = height;
    m_width = width;
    glViewport(0, 0, width, height);
}
