#include <fstream>
#include <sstream>
#include <iostream>

#include "ResourceManager.h"
#include "../Renderer/ShaderProgram.h"



ResourceManager::ResourceManager(const std::string& executablePath)
{
    size_t found = executablePath.find_last_of("/\\");
    m_path = executablePath.substr(0, found);
}

std::string ResourceManager::getFileString(const std::string& relativeFilePath)
{
    std::ifstream f;
    f.open(m_path + "/" + relativeFilePath, std::ios::in | std::ios::binary);
    if(!f.is_open())
    {
        std::cerr << "Erorr. Failed to open file: " << relativeFilePath << std::endl;
        return std::string{};
    }

    std::stringstream buffer;
    buffer << f.rdbuf();
    return buffer.str();

}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::loadShader(std::string& shaderName, std::string& vertexPath, std::string& fragmentPath)
{
    std::string vertexString = getFileString(vertexPath);
    if(vertexString.empty())
    {
        std::cerr << "Error. Vertex string is empty." << std::endl;
        return nullptr;
    }

    std::string fragmentString = getFileString(fragmentPath);
    if(fragmentString.empty())
    {
        std::cerr << "Error. Fragment string is empty." << std::endl;
        return nullptr;
    }
    std::shared_ptr<Renderer::ShaderProgram> newShader = m_ShaderPrograms.emplace(shaderName, std::make_shared<Renderer::ShaderProgram>(vertexString, fragmentString)).first->second;
    if(newShader->isCompiled())
    {
        return newShader;
    }

    std::cerr << "Shader is't compiled!" << std::endl;
    return nullptr;
}
