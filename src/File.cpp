#include "../inc/File.hpp"
#include "../inc/Directory.hpp"
#include "../inc/RegularFile.hpp"
#include <stdexcept>
#include <iostream>

File::File(int type, std::string name, std::string path, std::string lastModified)
{
    try
    {
        setType(type);
        setName(name);
        setPath(path);
        setLastModified(lastModified);
    }
    catch (std::invalid_argument& e) {
        throw e;
    }
}

void File::setType(int type)
{
    if (type != REGULAR_FILE && type != LINK && type != DIRECTORY)
        throw std::invalid_argument("[ERROR] Type must be REGULAR_FILE, LINK or DIRECTORY");
    this->type = type;
}

void File::setName(std::string name)
{
    if (name.empty())
        throw std::invalid_argument("[ERROR] File name cannot be empty");
    this->name = name;
}

void File::setPath(std::string path)
{
    if (path.empty())
        throw std::invalid_argument("[ERROR] Path cannot be empty");
    this->path = path;
}

void File::setLastModified(std::string lastModified)
{
    this->lastModified = lastModified;
}

void File::ls() const
{
    std::cout   << static_cast<char>(type) << " "
                << name << "      "
                << lastModified << std::endl;
}

void File::cat() const
{
    //TODO
}


std::string File::getDir() const
{

    if (path.find_last_of("/") == 0)
        return "/";
    return path.substr(0, path.find_last_of("/"));
}


File::~File()
{
    if (name.empty() == false)
        name.clear();
    if (path.empty() == false)
        path.clear();
    if (lastModified.empty() == false)
        lastModified.clear();
}