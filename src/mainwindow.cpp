#include "mainwindow.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

GLint windowHeight = 480;
GLint windowWidth = 640;

void glfwWindowSizeCallBack(GLFWwindow* pWindow, GLint width, GLint height)
{
    (void)pWindow;
    windowHeight = height;
    windowWidth = width;
    glViewport(0, 0, windowHeight, windowWidth);
    return;
}

void glfwWindowKeyCallBack(GLFWwindow* pWindow, int key, int scancode, int action, int mods)
{
    (void)scancode;
    (void)mods;
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
    }
    return;
}

MainWindow::MainWindow(const std::string title)
{
    if(!glfwInit())
    {
        std::cerr << "glfwInit() error" << std::endl;
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    const char* windowTitle = title.c_str();
    m_pWindow = glfwCreateWindow(windowWidth, windowHeight, windowTitle, nullptr, nullptr);
    if(!m_pWindow)
    {
        glfwTerminate();
        std::cerr << "glfwCreateWindow() error" << std::endl;
        return;
    }
    glfwSetWindowSizeCallback(m_pWindow, glfwWindowSizeCallBack);
    glfwSetKeyCallback(m_pWindow, glfwWindowKeyCallBack);
    glfwMakeContextCurrent(m_pWindow);

    if(!gladLoadGL())
    {
        glfwDestroyWindow(m_pWindow);
        glfwTerminate();
        std::cerr<< "gladLoadGL() error" << std::endl;
        return;
    }

    std::cout<< "Renderer " << glGetString(GL_RENDERER) << std::endl;
    std::cout<< "Version "  << glGetString(GL_VERSION)  << std::endl;

    m_isCreated = true;
}

void MainWindow::ClearColor(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
    return;
}

bool MainWindow::isCreated()
{
    return m_isCreated;
}

int MainWindow::WindowHeight()
{
    return windowHeight;
}

int MainWindow::WindowWidth()
{
    return windowWidth;
}

GLFWwindow* MainWindow::getWindow()
{
    return m_pWindow;
}


MainWindow::~MainWindow()
{
    if(m_isCreated)
    {
        glfwDestroyWindow(m_pWindow);
        glfwTerminate();
    }
}
