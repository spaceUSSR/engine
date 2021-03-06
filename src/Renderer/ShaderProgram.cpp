#include <glad/glad.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>
#include "ShaderProgram.h"
namespace Renderer
{

ShaderProgram::ShaderProgram(const std::string &vShaderPath, const std::string &fShaderPath)
{

    std::string vShaderSource = shaderSource(vShaderPath);
    std::string fShaderSource = shaderSource(fShaderPath);

    /* Compile shaders */
	uint vertexShader, fragmentShader;
    if(!createShader(vertexShader, GL_VERTEX_SHADER, vShaderSource.c_str()))
    {
        return;
    }
	if(!createShader(fragmentShader, GL_FRAGMENT_SHADER, fShaderSource.c_str()))
    {
        glDeleteShader(vertexShader);
        return;
    }

     /* Create and link shader program */
    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, vertexShader);
    glAttachShader(m_shaderProgram, fragmentShader);
    glLinkProgram(m_shaderProgram);

    /* Get result shader program linking */
    GLint seccess;
	glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &seccess);
    if(seccess)
    {
		compiled = true;
    }
    else
    {
        char infoLog[1024];
        glGetProgramInfoLog(m_shaderProgram, sizeof (infoLog), NULL, infoLog);
        std::cout<< infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void ShaderProgram::use() const
{
    glUseProgram(m_shaderProgram);
}

int ShaderProgram::getUniformLocation(const std::string &uniform) const
{
    return glGetUniformLocation(m_shaderProgram, uniform.c_str());
}

bool ShaderProgram::isCompiled() const
{
	return compiled;
}

bool ShaderProgram::createShader(uint &shader, GLenum shaderType, const char *shaderSource)
{
    shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);

    GLint seccess;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &seccess);
    if(!seccess)
    {
		char infoLog[1024];
		glGetShaderInfoLog(shader, sizeof (infoLog), NULL, infoLog);
		std::cout<< "Error: " << ((shaderType == GL_FRAGMENT_SHADER)? "fragment shader " : " vertex shader ") << infoLog << std::endl;
		return false;
    }
    return true;
}

std::string ShaderProgram::shaderSource(const std::string &sourcePath) const
{
    std::string soureCode;
    std::ifstream shaderFile;
    shaderFile.exceptions(std::ifstream::badbit);
    try
    {
        shaderFile.open(sourcePath);
        std::stringstream shaderStream;

        shaderStream << shaderFile.rdbuf();
        shaderFile.close();

        soureCode = shaderStream.str();

    }  catch (std::ifstream::failure& e)
    {
        std::cout << "Get shader source error!"<< std::endl << e.what() << std::endl;
    }
    return soureCode;
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(m_shaderProgram);
}

void ShaderProgram::setInt(const std::string &uniform, int data) const
{
	glUniform1i(glGetUniformLocation(m_shaderProgram, uniform.c_str()), data);
}

void ShaderProgram::setData(const std::string &uniform, float data) const
{
	glUniform1f(glGetUniformLocation(m_shaderProgram, uniform.c_str()), data);
}

void ShaderProgram::setData(const std::string &uniform, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(m_shaderProgram, uniform.c_str()), x, y, z);
}

void ShaderProgram::setVec3(const std::string& uniform, const glm::vec3& vec) const
{
	glUniform3f(glGetUniformLocation(m_shaderProgram, uniform.c_str()), vec.x, vec.y, vec.z);
}

void ShaderProgram::setMat4(const std::string &uniform, const glm::mat4 &mat, uint count, bool shouldTranspose) const
{
	glUniformMatrix4fv(glGetUniformLocation(m_shaderProgram, uniform.c_str()), count, shouldTranspose, glm::value_ptr(mat));
}

}
