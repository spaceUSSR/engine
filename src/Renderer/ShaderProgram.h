#pragma once

#include <string>
#include <iostream>

namespace Renderer {
typedef unsigned int GLuint;

class ShaderProgram{
public:
    ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
    ShaderProgram() = delete;
    ShaderProgram(ShaderProgram&) = delete;
    ShaderProgram(ShaderProgram&& shaderProgram) noexcept;
    ~ShaderProgram();


    ShaderProgram& operator = (const ShaderProgram&) = delete;
    ShaderProgram& operator = (ShaderProgram&& shaderProgram) noexcept;

     bool isCompiled();
     void use() const;
private:
    bool createShader(const std::string& source, GLenum shaderType, GLuint& shaderID);


    bool m_isCompiled = false;
    GLuint m_ID = 0;

};


};
