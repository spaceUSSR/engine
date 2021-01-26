#ifndef SHADERPROGRAM_H_
#define SHADERPROGRAM_H_

#include <string>

typedef unsigned int uint;
typedef unsigned int GLenum;

namespace Renderer {
class ShaderProgram{
public:
    ShaderProgram(const std::string &vShaderPath, const std::string &fShaderPath);
    ~ShaderProgram();

    void setInt(const std::string& uniform, int data) const;
    void setData(const std::string& uniform, float data) const;

    void useShaderProgram() const;
    int getUniformLocation(const std::string& uniform) const;
private:
    uint m_shaderProgram;

    bool createShader(uint& shader, GLenum shaderType, const char* shaderSource);
    std::string shaderSource(const std::string& shaderSourcePath) const;
};
};

#endif
