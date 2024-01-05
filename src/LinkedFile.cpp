#include "../inc/LinkedFile.hpp"

// LinkedFile::LinkedFile(): File(LINKED_FILE)
// {

// }

LinkedFile::LinkedFile(std::string name, std::string path, std::string lastModified, File* linkedFile): File(LINK, name, path, lastModified)
{
    this->linkedFile = linkedFile;
}

