#include "../inc/Directory.hpp"
#include <iostream>
#include "../inc/RegularFile.hpp"

using std::string;
using std::vector;
using std::cout;
using std::endl;

Directory::Directory()
{
    /*DEFAULT CONSTRUCTORU KULLANMAYI ENGELLEYEBİLİRİM*/
}

Directory::Directory(std::string name, std::string path, std::string lastModified): File(DIRECTORY, name, path, lastModified)
{
    /*PARAMETERIZED CONSTRUCTOR*/
    /*BURAYA BİR ŞEY GELEBİLİR*/
}

void Directory::setFiles(std::vector<File *> files)
{
    this->files = files;
}

void Directory::setPrevDir(Directory* prevDir)
{
    this->prevDir = prevDir;
}

void Directory::addFile(File *file)
{
    files.push_back(file);
}

void Directory::ls() const
{
    for (auto file : files)
    {
        std::cout   << static_cast<char>(file->getType()) << " "
                << file->getName() << "      "
                << file->getLastModified() << std::endl;
    }
}

File* Directory::findFileInCurrentByName(const std::string& name)
{
    for (auto file : files)
    {
        if (file->getName() == name)
            return file;
    }
    return nullptr;
}

Directory* Directory::findDirInCurrentByPath(const std::string& path)
{
    for (auto file : files)
    {
        if (file->getType() == DIRECTORY && file->getPath() == path)
            return static_cast<Directory *>(file);
    }
    return nullptr;
}

Directory::~Directory()
{
    for (auto file : files)
        delete file;
}
