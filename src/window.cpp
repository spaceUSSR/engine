#include "window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

GLFWwindow* Window::m_window = 0;
int Window::m_height = 480;
int Window::m_width = 640;

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
    glfwSetKeyCallback(m_window, glfwWindowKeyCallBack);

    /* Make the window's context current */
    glfwMakeContextCurrent(m_window);

    if(!gladLoadGL())
    {
        glfwDestroyWindow(m_window);
        glfwTerminate();
        return 3;
    }

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

void Window::pollEvents()
{
    glfwPollEvents();
}

void Window::clearColor(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

int Window::getKey(int key)
{
    return glfwGetKey(m_window, key);
}

int Window::finalize()
{
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

void Window::glfwWindowKeyCallBack(GLFWwindow* pWindow, int key, int scancode, int action, int mods)
{
    (void)scancode;
    (void)mods;
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(pWindow, GLFW_TRUE);

    if(key == GLFW_KEY_LEFT_CONTROL && action == GLFW_PRESS)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else if(key == GLFW_KEY_LEFT_CONTROL && action == GLFW_RELEASE)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}
