#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Renderer/ShaderProgramm.h"

int windowWidth = 640;
int windowHeight = 480;

GLfloat point[] = {  0.0f,   0.5f,  0.0f,
                     0.5f,  -0.5f,  0.0f,
                    -0.5f,  -0.5f,  0.0f};

GLfloat color[] = { 1.0f, 0.0f, 0.0f,
                    0.0f, 1.0f, 0.0f,
                    0.0f, 0.0f, 1.0f};

const char* vertex_shader = "#version 460\n"
"layout(location = 0 ) in vec3 vector_pos;"
"layout(location = 1 ) in vec3 vector_col;"
"out vec3 color;"
"void main(){"
"   color = vector_col;"
"   gl_Position = vec4(vector_pos, 1.0);"
"}";

const char* fragment_shader = "#version 460\n"
"in vec3 color;"
"out vec4 fragment_color;"
"void main(){"
"   fragment_color = vec4(color, 1.0);"
"}";

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

    glClearColor(0.5f, 0.5f, 0.5f, 1);

    std::string vertexShader(vertex_shader);
    std::string fragmentShader(fragment_shader);

    Renderer::ShaderProgramm shaderProgramm(vertexShader, fragmentShader);
    if(!shaderProgramm.isCompiled())
    {
        std::cerr<<"Shader is't compiled!" << std::endl;
        return -1;
    }

    GLuint points_vbo = 0;
    glGenBuffers(1, &points_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof (point), point, GL_STATIC_DRAW);

    GLuint colors_vbo = 0;
    glGenBuffers(1, &colors_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof (color), color, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, nullptr);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(pWindow))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgramm.use();
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        /* Swap front and back buffers */
        glfwSwapBuffers(pWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glfwDestroyWindow(pWindow);
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
