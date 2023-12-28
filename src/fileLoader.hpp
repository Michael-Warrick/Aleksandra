#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class FileLoader
{
public:
    static std::string LoadFromFile(const std::string& path);
};