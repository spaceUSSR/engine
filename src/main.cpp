#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

int windowWidth = 640;
int windowHeight = 480;

void glfwWindowSizeCallBack(GLFWwindow* pWindow, int width, int height);
void glfwWindowKeyCallBack(GLFWwindow* pWindow, int key, int scancode, int action, int mods);

int main(void)
{
    if (!glfwInit())
    {
        std::cout<< "glfwInit() error!" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* pWindow;
    pWindow = glfwCreateWindow(windowWidth, windowHeight, "Hello World", nullptr, nullptr);
    if (!pWindow)
    {
        glfwTerminate();
        return -2;
    }

    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallBack);
    glfwSetKeyCallback(pWindow, glfwWindowKeyCallBack);

    /* Make the window's context current */
    glfwMakeContextCurrent(pWindow);

    if(!gladLoadGL())
    {
        std::cout<< "gladLoadGL() error!" << std::endl;
        return -3;
    }

    std::cout<< "Renderer " << glGetString(GL_RENDERER) << std::endl;
    std::cout<< "Version "  << glGetString(GL_VERSION)  << std::endl;

    glClearColor(0, 1, 0, 1);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(pWindow))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        /* Swap front and back buffers */
        glfwSwapBuffers(pWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}



void glfwWindowSizeCallBack(GLFWwindow* pWindow, int width, int height)
{
    (void)pWindow;
    windowHeight = height;
    windowWidth = width;
    glViewport(0, 0, width, height);
    return;
}

void glfwWindowKeyCallBack(GLFWwindow* pWindow, int key, int scancode, int action, int mods)
{
    (void)scancode;
    (void)mods;
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(pWindow, GLFW_TRUE);
}
