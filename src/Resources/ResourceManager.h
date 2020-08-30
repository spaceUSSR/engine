#pragma once

#include <string>
#include <memory>
#include <map>

namespace  Renderer{class ShaderProgram;};

class ResourceManager
{
public:
    ResourceManager(const std::string& executablePath);
    ~ResourceManager() = default;

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager(ResourceManager&&) = delete;

    ResourceManager& operator= (const ResourceManager&) = delete;
    ResourceManager& operator= (ResourceManager&&) = delete;


    std::shared_ptr<Renderer::ShaderProgram> loadShader(std::string& shaderName, std::string& vertexPath, std::string& fragmentPath);
    std::shared_ptr<Renderer::ShaderProgram> getShader(std::string& shaderName);

private:
    std::string getFileString(const std::string& relativeFilePath);

    typedef std::map<std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramMap;
    ShaderProgramMap m_ShaderPrograms;
    std::string m_path;



};
