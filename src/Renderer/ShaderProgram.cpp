#include <glad/glad.h>
#include "ShaderProgram.h"

namespace Renderer {

bool ShaderProgram::isCompiled()
{
    return this->m_isCompiled;
}

ShaderProgram::ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader)
{
    GLuint vertexShaderID;
    if(!createShader(vertexShader, GL_VERTEX_SHADER, vertexShaderID))
    {
        std::cerr << "Vertex shader compile error!" << std::endl;
        return;
    }

    GLuint fragmentShaderID;
    if(!createShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderID))
    {
        glDeleteShader(vertexShaderID);
        std::cerr << "Fragment shader compile error!" << std::endl;
        return;
    }


    m_ID = glCreateProgram();
    glAttachShader(m_ID, vertexShaderID);
    glAttachShader(m_ID, fragmentShaderID);
    glLinkProgram(m_ID);


    GLint result;
    glGetProgramiv(m_ID, GL_LINK_STATUS, &result);
    if(!result)
    {
        GLchar infoLog[1024];
        glGetShaderInfoLog(m_ID, sizeof (infoLog), nullptr, infoLog);
        std::cerr << "ERROR::SHADER link-time error!" << infoLog << std::endl;
    }
    else
    {
        m_isCompiled = true;
    }

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
}


bool ShaderProgram::createShader(const std::string& source, GLenum shaderType, GLuint& shaderID)
{
    const GLchar* sourceCode = source.c_str();

    shaderID = glCreateShader(shaderType);
    glShaderSource(shaderID, 1, &sourceCode, nullptr);
    glCompileShader(shaderID);

    GLint result;
    glGetShaderiv(shaderID, shaderType, &result);
    if(!result)
    {
        GLchar infoLog[1024];
        glGetShaderInfoLog(shaderID, sizeof (infoLog), nullptr, infoLog);
        std::cerr << "ERROR::SHADER compile-time error!" << infoLog << std::endl;
        return false;
    }
    return true;

}
void ShaderProgram::use() const
{
    glUseProgram(m_ID);
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(m_ID);
}
ShaderProgram::ShaderProgram(ShaderProgram&& shaderProgramm) noexcept
{
    this->m_ID = shaderProgramm.m_ID;
    this->m_isCompiled = shaderProgramm.m_isCompiled;

    shaderProgramm.m_isCompiled = false;
    shaderProgramm.m_ID = 0;
}
ShaderProgram& ShaderProgram::operator = (ShaderProgram&& shaderProgramm) noexcept
{
    glDeleteProgram(this->m_ID);
    this->m_ID = shaderProgramm.m_ID;
    this->m_isCompiled = shaderProgramm.m_isCompiled;

    shaderProgramm.m_isCompiled = false;
    shaderProgramm.m_ID = 0;
    return *this;
}
};

