#include "../inc/LinkedFile.hpp"
#include <iostream>

using std::cout;
using std::endl;
using std::string;

LinkedFile::LinkedFile(std::string name, std::string path, std::string lastModified, File* linkedFile): File(LINK, name, path, lastModified)
{
    if (linkedFile->getType() == LINK)
    {
        LinkedFile *link = static_cast<LinkedFile *>(linkedFile);
        this->linkedFile = link->getLinkedFile();
        this->linkedFileName = link->getLinkedFileName();
        this->linkedFilePath = link->getLinkedFilePath();
    }
    else if (linkedFile->getType() == REGULAR_FILE || linkedFile->getType() == DIRECTORY)
    {
        this->linkedFile = linkedFile;
        this->linkedFileName = linkedFile->getName();
        this->linkedFilePath = linkedFile->getPath();
    }
    else
    {
        this->linkedFile = nullptr;
    }
}

void LinkedFile::ls() const
{
    std::cout   << BLUE << static_cast<char>(type) << DEFAULT << " "
                << name << "      "
                << CYAN  << lastModified << DEFAULT<< "  " << BLUE << name << WHITE << "->" << RED  << linkedFilePath
                    << DEFAULT << std::endl;
}

void LinkedFile::cat() const
{
    if (linkedFile == nullptr)
        throw std::runtime_error(NO_LINK);
    if (linkedFile->getType() == DIRECTORY)
        throw std::runtime_error(IS_DIR);
    else
        linkedFile->cat();
}

std::ostream& operator<<(std::ostream& os, const LinkedFile& file)
{
    string link = file.name + "->" + file.linkedFilePath;
    os  << static_cast<char>(file.type) << " "
        << file.name << " " << file.path << " "
        << file.lastModified << " " << link;
    return os;
}

LinkedFile::~LinkedFile()
{
    linkedFile = nullptr;
    linkedFileName.clear();
    linkedFilePath.clear();
}