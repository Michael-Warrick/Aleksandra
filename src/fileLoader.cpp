#include "fileLoader.hpp"

std::string FileLoader::LoadFromFile(const std::string& path)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        throw std::runtime_error("Unable to open file: " + path);
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}