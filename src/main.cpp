#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "window.h"
#include "Renderer/ShaderProgram.h"
//#include "Renderer/texture.h"
//#include "camera.h"
//#include "events.h"
//#include <cmath>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
#include <iostream>
float yaw = -90.0f;
float pitch = 0.0f;


int main(void)
{
	Window::initialize(1920, 1080, "my window");
	{
		Renderer::ShaderProgram lightShader("res/shaders/lightShader.glslv", "res/shaders/lightShader.glslf");
		if(!lightShader.isCompiled())
			std::cout << " lightShader isn't compiled" << std::endl;

		Renderer::ShaderProgram cubeShader("res/shaders/shader.glslv", "res/shaders/shader.glslf");
		if(!cubeShader.isCompiled())
			std::cout << " Shader program isn't compiled" << std::endl;
//                                /* Points         */    /* Texture*/
//		float vertices[] = { -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

//                                    0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
//                                    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//                                    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//                                   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//                                   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

//                                   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//                                    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//                                    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//                                    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//                                   -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
//                                   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

//                                   -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//                                   -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//                                   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//                                   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//                                   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//                                   -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

//                                    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//                                    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//                                    0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//                                    0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//                                    0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//                                    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

//                                   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//                                    0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
//                                    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//                                    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//                                   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//                                   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

//                                   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//                                    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//                                    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//                                    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//                                   -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
//                                   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f};


//        //create vao1
//        uint vbo, vao;
//		glGenVertexArrays(1, &vao);
//        glBindVertexArray(vao);

//        glGenBuffers(1, &vbo);
//        glBindBuffer(GL_ARRAY_BUFFER, vbo);
//        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
//        glEnableVertexAttribArray(0);

//        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof (float), (void*)(sizeof (float) * 3));
//		glEnableVertexAttribArray(2);

//		uint lightVAO;
//		glGenVertexArrays(1, &lightVAO);
//		glBindVertexArray(lightVAO);
//		glBindBuffer(GL_VERTEX_ARRAY, vbo);

//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof (float), nullptr);
//		glEnableVertexAttribArray(0);


//		/* Textures */
//		Renderer::Texture cubeTexture("res/textures/container.jpg");
//		Renderer::Texture terrainTexture("res/textures/terrain.jpg");


//        float wHeight = static_cast<float>(Window::getHeight());
//        float wWidth = static_cast<float>(Window::getWidth());
//        glm::mat4 proejection = glm::perspective(glm::radians(45.0f), wHeight/wWidth, 0.1f, 100.0f);


//		shaderProgram.useShaderProgram();
//        shaderProgram.setData("projection", glm::value_ptr(proejection));
//		shaderProgram.setData("lightColor", 0.5f, 0.5f, 0.5f);

//		glm::mat4 terrainModel(1.0f);
//		terrainModel = glm::scale(terrainModel, glm::vec3(2.0f, 2.0f, 2.0f));


//		lightShader.useShaderProgram();
//		glm::mat4 lightCubeModel = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
//		lightCubeModel = glm::scale(lightCubeModel, glm::vec3(0.4f, 0.4f, 0.4f));
//		lightShader.setData("projection", glm::value_ptr(proejection));
//		lightShader.setData("model", glm::value_ptr(lightCubeModel));


//        /* Render cycle */
//        while(!Window::isSouldClose())
//        {
//            Window::clearColor(0.1f, 0.2f, 0.3f);
//			glm::mat4 view = Camera::look();

//			/* Draw cubes*/
//			cubeTexture.use(GL_TEXTURE0);

//			glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(0.4, 0.4f, 0.4f));
//			model = glm::rotate(model, static_cast<float>(glfwGetTime()), glm::vec3(1.0f, 0.3f, 0.5f));

//			shaderProgram.useShaderProgram();
//			shaderProgram.setData("view", glm::value_ptr(view));
//			shaderProgram.setData("model", glm::value_ptr(model));

//			glBindVertexArray(vao);
//			glDrawArrays(GL_TRIANGLES, 0, 36);


//			/* Draw light cube */
//			lightShader.useShaderProgram();
//			lightShader.setData("view", glm::value_ptr(view));
//			glBindVertexArray(lightVAO);
//			glDrawArrays(GL_TRIANGLES, 0, 36);



//            Window::swapBuffers();
//			Events::pollEvents();
//        }

//        glDeleteVertexArrays(1, &vao);
//		glDeleteVertexArrays(1, &lightVAO);
//        glDeleteBuffers(1, &vbo);
    }
    Window::finalize();
    return 0;
}
