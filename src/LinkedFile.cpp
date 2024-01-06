#include "../inc/LinkedFile.hpp"
#include <iostream>

using std::cout;
using std::endl;
using std::string;

// LinkedFile::LinkedFile(): File(LINKED_FILE)
// {

// }

LinkedFile::LinkedFile(std::string name, std::string path, std::string lastModified, File* linkedFile): File(LINK, name, path, lastModified)
{
    this->linkedFile = linkedFile;
}

void LinkedFile::ls() const
{
    string linkName;
    if (this->linkedFile != nullptr)
        linkName = linkedFile->getName();
    std::cout   << static_cast<char>(type) << " "
                << name+"->"+linkName << "      "
                << lastModified << "  " << std::endl;
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

LinkedFile::~LinkedFile()
{
    linkedFile = nullptr;
}