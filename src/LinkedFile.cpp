#include "../inc/LinkedFile.hpp"
#include <iostream>

using std::cout;
using std::endl;
using std::string;

namespace FileSystem
{
    LinkedFile::LinkedFile(std::string name, std::string path, std::string lastModified,
        string linkName, std::string linkPath, File* linkedFile): File(LINK, name, path, lastModified)
    {
        this->linkedFileName = linkName;
        this->linkedFilePath = linkPath;
        if (linkedFile == nullptr)
            this->linkedFile = nullptr;
        else if (linkedFile->getType() == LINK)
        {
            LinkedFile *link = static_cast<LinkedFile *>(linkedFile);
            this->linkedFile = link->getLinkedFile();
        }
        else if (linkedFile->getType() == REGULAR_FILE || linkedFile->getType() == DIRECTORY)
            this->linkedFile = linkedFile;
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

    LinkedFile::LinkedFile(const LinkedFile& other): File(other)
    {
        //deep copy
        this->linkedFileName = other.linkedFileName;
        this->linkedFilePath = other.linkedFilePath;
        if (other.linkedFile == nullptr)
            this->linkedFile = nullptr;
        else if (other.linkedFile->getType() == LINK)
        {
            LinkedFile *link = static_cast<LinkedFile *>(other.linkedFile);
            this->linkedFile = link->getLinkedFile();
        }
        else if (other.linkedFile->getType() == REGULAR_FILE || other.linkedFile->getType() == DIRECTORY)
            this->linkedFile = other.linkedFile;
    }

    LinkedFile::~LinkedFile()
    {
        linkedFile = nullptr;
        linkedFileName.clear();
        linkedFilePath.clear();
    }
}