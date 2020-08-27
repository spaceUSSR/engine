#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


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
    GLFWwindow* winptr;
    winptr = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    if (!winptr)
    {
        glfwTerminate();
        return -2;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(winptr);

    if(!gladLoadGL())
    {
        std::cout<< "gladLoadGL() error!" << std::endl;
        return -3;
    }

    std::cout<< "Renderer " << glGetString(GL_RENDERER) << std::endl;
    std::cout<< "Version "  << glGetString(GL_VERSION)  << std::endl;

    /* Loop until the user closes the window */
    glClearColor(0, 1, 0, 1);
    while (!glfwWindowShouldClose(winptr))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        /* Swap front and back buffers */
        glfwSwapBuffers(winptr);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
