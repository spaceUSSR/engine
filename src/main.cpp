#include <iostream>
#include "window.h"
#include "Renderer/ShaderProgram.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <time.h>
#include <cmath>
#include <stb_image.h>


int main(void)
{
    Window::initialize(640, 480, "my window");
    {
        Renderer::ShaderProgram shaderProgram("res/shaders/shader.glslv", "res/shaders/shader.glslf");

        /* Create first object */
                                /* Points         */    /* Colors         */    /* Texture*/
        float vertices[] = {    -0.5f,  0.5f,   0.0f,   1.0f,   0.0f,   0.0f,   0.0f, 2.0f, // top left
                                -0.5f,  -0.5f,  0.0f,   0.0f,   1.0f,   0.0f,   0.0f, 0.0f, // bottom left
                                 0.5f,   0.5f,  0.0f,   0.0f,   0.0f,   1.0f,   2.0f, 2.0f, // top right
                                 0.5f,  -0.5f,  0.0f,   1.0f,   1.0f,   0.0f,   2.0f, 0.0f}; // bottom right
        uint indices[] = {0, 2, 3,
                          0, 1, 3};

        uint vbo, vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof (float), (void*)(sizeof (float) * 3));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof (float), (void*)(sizeof (float) * 6));
        glEnableVertexAttribArray(2);

        uint ebo;
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof (indices), indices, GL_STATIC_DRAW);

        /* Textures */
        int width, height, nrChanel;
        uint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load("res/textures/container.jpg", &width, &height, &nrChanel, 0);
        if(data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
            stbi_image_free(data);
        } else {
            std::cout << "Texture load error!" << std::endl;
        }

        uint texture2;
        glGenTextures(1, &texture2);
        glBindTexture(GL_TEXTURE_2D, texture2);

        glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        data = stbi_load("res/textures/top_secret.png", &width, &height, &nrChanel, 0);
        if(data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
            stbi_image_free(data);
        } else {
            std::cout << "Top secret texture load error!" << std::endl;
        }

//        uint location = shaderProgram.getUniformLocation("shift");
        shaderProgram.useShaderProgram();
        shaderProgram.setInt("texture2", 1);
        float visibleStatus = 0;

        /* Render cycle */
        while(!Window::isSouldClose())
        {
            Window::clearColor(0.1f, 0.2f, 0.3f);

            shaderProgram.useShaderProgram();
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture);

            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, texture2);

            glBindVertexArray(vao);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

            shaderProgram.setData("visibleStatus", visibleStatus);
            if(Window::getKey(GLFW_KEY_UP) == GLFW_PRESS) {
                visibleStatus+= 0.05;
            } else if(Window::getKey(GLFW_KEY_DOWN) == GLFW_PRESS) {
                visibleStatus-= 0.05;
            }

//            glUniform1f(location, 0.5);

//            glDrawArrays(GL_TRIANGLES, 0, 6);

            Window::swapBuffers();
            Window::pollEvents();
        }

        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ebo);
    }
    Window::finalize();
    return 0;
}
