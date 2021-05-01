#include "window.h"
#include "events.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Window::Window(const std::string &title, int width, int height) :
    m_title(title), m_height(height), m_width(width)
{
    init();
}

Window::~Window()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void Window::init()
{
    if(!glfwInit())
        return;
    m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);
    if(!m_window)
        return;
    glfwMakeContextCurrent(m_window);

    if(!gladLoadGL())
        return;
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

void Window::pollEvents()
{
    glfwPollEvents();
}


//void Window::glfwWindowSizeCallBack(GLFWwindow *pWindow, int width, int height)
//{
////    (void)pWindow;
////    m_height = height;
////    m_width = width;
////    glViewport(0, 0, width, height);
//}
