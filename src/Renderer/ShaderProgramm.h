#pragma once

#include <glad/glad.h>
#include <string>
#include <iostream>

namespace Renderer {


class ShaderProgramm{
public:
    ShaderProgramm(const std::string& vertexShader, const std::string& fragmentShader);
    ShaderProgramm() = delete;
    ShaderProgramm(ShaderProgramm&) = delete;
    ShaderProgramm(ShaderProgramm&& shaderProgramm) noexcept;
    ~ShaderProgramm();


    ShaderProgramm& operator = (const ShaderProgramm&) = delete;
    ShaderProgramm& operator = (ShaderProgramm&& shaderProgramm) noexcept;

     bool isCompiled();
     void use() const;
private:
    bool createShader(const std::string& source, GLenum shaderType, GLuint& shaderID);


    bool m_isCompiled = false;
    GLuint m_ID = 0;

};


};
