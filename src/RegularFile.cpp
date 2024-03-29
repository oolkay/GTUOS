#include "../inc/RegularFile.hpp"
#include <stdexcept>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

namespace FileSystem
{ 
    RegularFile::RegularFile(std::string name, std::string path,
            std::string lastModified, std::string content, size_t size): File(REGULAR_FILE, name, path, lastModified)
    {
        /*PARAMETERIZED CONSTRUCTOR*/
        this->content = content;
        this->size = size;
    }


    void RegularFile::setContent(std::string content)
    {
        this->content = content;
    }

    void RegularFile::setSize(size_t size)
    {
        this->size = size;
    }

    std::ostream& operator<<(std::ostream& os, const RegularFile& regFile)
    {
        os << static_cast<char>(regFile.getType()) << " " << regFile.getName() << " " << regFile.getPath()
            << " " << regFile.getLastModified() << " " << regFile.getSize() << "Bytes" << "\n%\n"
            << regFile.getContent() << "\n%";
        return os;
    }

    void RegularFile::ls() const
    {
        std::cout   << GREEN << static_cast<char>(type)<< " "
                    << name << "      "   
                    << CYAN << lastModified << DEFAULT << "  "
                    << size << "Bytes" << std::endl;
    }

    void RegularFile::cat() const
    {
        std::cout << content << std::endl;
    }


    RegularFile::~RegularFile()
    {
        if (content.empty() == false)
            content.clear();
    }
}