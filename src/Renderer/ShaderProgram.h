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

//    void setInt(const std::string& uniform, int data) const;
//    void setData(const std::string& uniform, float data) const;
//    void setData(const std::string& uniform, const float* data, uint count = 1, bool shouldTranspose = false);
//	void setData(const std::string& uniform, float x, float y, float z);

    void useShaderProgram() const;
    int getUniformLocation(const std::string& uniform) const;
	bool isCompiled() const;

private:
	uint m_shaderProgram;
	bool compiled = false;

    bool createShader(uint& shader, GLenum shaderType, const char* shaderSource);
    std::string shaderSource(const std::string& shaderSourcePath) const;
};
};

#endif
