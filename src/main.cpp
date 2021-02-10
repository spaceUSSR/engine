#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "window.h"
#include "Renderer/ShaderProgram.h"
#include "Renderer/texture.h"
#include "camera.h"
#include "events.h"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "mesh.h"
float yaw = -90.0f;
float pitch = 0.0f;


int main(void)
{
	Window::initialize(1920, 1080, "Engine");
	{
		float vertices[] = {		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
									0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
									0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
									0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
								   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f, -1.0f,
								   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 0.0f, -1.0f,

								   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
									0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
									0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
									0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
								   -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
								   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f,

								   -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
								   -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
								   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
								   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
								   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
								   -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f, 0.0f, 0.0f,

									0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
									0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
									0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
									0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
									0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
									0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f,

								   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
									0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
									0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
									0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
								   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
								   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f, 0.0f,

								   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
									0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
									0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
									0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
								   -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
								   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f};

		glm::vec3 cubePositions[] = {
			glm::vec3( 0.0f,  0.0f,  0.0f),
			glm::vec3( 2.0f,  5.0f, -15.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(-3.8f, -2.0f, -12.3f),
			glm::vec3( 2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f,  3.0f, -7.5f),
			glm::vec3( 1.3f, -2.0f, -2.5f),
			glm::vec3( 1.5f,  2.0f, -2.5f),
			glm::vec3( 1.5f,  0.2f, -1.5f),
			glm::vec3(-1.3f,  1.0f, -1.5f)
		};

		/* Cube */
		uint vbo, vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof (float), (void*)(sizeof (float) * 3));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof (float), (void*)(sizeof (float) * 5));
		glEnableVertexAttribArray(2);

		/* Light cube */
		uint lightVAO;
		glGenVertexArrays(1, &lightVAO);
		glBindVertexArray(lightVAO);
		glBindBuffer(GL_VERTEX_ARRAY, vbo);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof (float), nullptr);
		glEnableVertexAttribArray(0);

		float wHeight = static_cast<float>(Window::getHeight());
		float wWidth = static_cast<float>(Window::getWidth());
		glm::mat4 proejection = glm::perspective(glm::radians(45.0f), wWidth/wHeight, 0.1f, 100.0f);

		Renderer::ShaderProgram cubeShader("res/shaders/shader.vert", "res/shaders/shader.frag");
		cubeShader.use();
		cubeShader.setMat4("projection", proejection);
		cubeShader.setData("lightColor", 1.0f, 1.0f, 1.0f);
		cubeShader.setInt("material.ambient", 0);
;
		cubeShader.setInt("material.specular", 1);
		cubeShader.setInt("material.lines", 2);
		cubeShader.setData("material.shininess", 32.0f);


		/* Material */
		Renderer::Texture cubeTexture("res/textures/box.jpg", 0);
		Renderer::Texture cubeMapTexture("res/textures/box_map.jpg", 1);
		Renderer::Texture linesTexture("res/textures/lines.jpg", 2);

		cubeShader.setData("light.ambient" , 0.1f, 0.1f, 0.1f);
		cubeShader.setData("light.diffuse" , 0.8f, 0.8f, 0.8f);
		cubeShader.setData("light.specular" , 1.0f, 1.0f, 1.0f);

		cubeShader.setData("light.constant", 1.0f);
		cubeShader.setData("light.linear", 0.09f);
		cubeShader.setData("light.quadritic", 0.032f);


		glm::mat4 lightCubeModel(1.0f);
		glm::vec3 lightPos(1.0f, 1.0f, 1.0f);
		lightCubeModel = glm::translate(lightCubeModel, lightPos);
		lightCubeModel = glm::scale(lightCubeModel, glm::vec3(0.2f, 0.2f, 0.2f));

		Renderer::ShaderProgram lightShader("res/shaders/lightShader.vert", "res/shaders/lightShader.frag");
		lightShader.use();
		lightShader.setMat4("projection", proejection);
		lightShader.setMat4("model", lightCubeModel);

		while(!Window::isSouldClose())
		{
			Window::clearColor(0.1f, 0.1f, 0.1f);
			glm::mat4 view = Camera::look();


			/* Draw cube*/
			cubeShader.use();
			cubeShader.setMat4("view", view);
			cubeShader.setVec3("light.position", lightPos);
			cubeShader.setVec3("viewPos", Camera::position());

			cubeTexture.use();
			cubeMapTexture.use();
			linesTexture.use();
			glBindVertexArray(vao);
			for(int i = 0; i < 10; i++)
			{
				glm::mat4 cubeModel = glm::translate(glm::mat4(1.0f), cubePositions[i]);
				cubeModel = glm::scale(cubeModel, glm::vec3(0.5f, 0.5f, 0.5f));
				cubeShader.setMat4("model", cubeModel);
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}

			/* Draw light cube */
			lightShader.use();
			lightShader.setMat4("view", view);
			glBindVertexArray(lightVAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);

			Window::swapBuffers();
			Events::pollEvents();
		}

		glDeleteVertexArrays(1, &vao);
		glDeleteVertexArrays(1, &lightVAO);
		glDeleteBuffers(1, &vbo);
	}
	Window::finalize();
    return 0;
}
