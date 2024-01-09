#include "../inc/Directory.hpp"
#include <iostream>
#include "../inc/RegularFile.hpp"
#include "../inc/LinkedFile.hpp"

using std::string;
using std::vector;
using std::cout;
using std::endl;

namespace FileSystem
{
    Directory::Directory(std::string name, std::string path, std::string lastModified): File(DIRECTORY, name, path, lastModified)
    {
    }

    Directory::Directory(const Directory& other): File(other)
    {
        //deep copy, recursively
        for (auto file : other.files)
        {
            string name = file->getName();
            string path = file->getPath();
            if (file->getType() == REGULAR_FILE)
                this->files.push_back(new RegularFile(*static_cast<RegularFile *>(file)));
            else if (file->getType() == DIRECTORY)
            {
                Directory *dir = static_cast<Directory *>(file);
                this->files.push_back(new Directory(*dir));
            }
            else if (file->getType() == LINK)
                this->files.push_back(new LinkedFile(*static_cast<LinkedFile *>(file)));
        }
    }

    void Directory::setPrevDir(Directory* prevDir)
    {
        this->prevDir = prevDir;
    }

    void Directory::addFile(File *file)
    {
        if (file == nullptr)
            throw std::invalid_argument("[ERROR] File cannot be nullptr");
        files.push_back(file);
        setLastModified(file->getLastModified());
    }

    void Directory::removeFile(File *file)
    {
        for (auto it = files.begin(); it != files.end(); ++it)
        {
            if (*it == file)
            {
                files.erase(it);
                delete file;
                return ;
            }
        }
    }

    void Directory::ls() const
    {

        std::cout  << YELLOW << DIRECTORY <<  " "
            << "." << DEFAULT << "      "
            << CYAN << this->getLastModified() << std::endl;
        if (this->name != "/")
        {
            std::cout  << YELLOW << DIRECTORY <<  " "
                << ".." << DEFAULT << "      "
                << CYAN << prevDir->getLastModified() << std::endl;
        }
        for (auto file : files)
        {
            if (file->getType() == REGULAR_FILE || file->getType() == LINK)
                file->ls();
            else
            {
                std::cout  << YELLOW << static_cast<char>(file->getType()) <<  " "
                    << file->getName() << DEFAULT << "      "
                    << CYAN << file->getLastModified() << std::endl;
            }
        }
    }

    void Directory::lsRecursive() const
    {
        std::cout << this->getPath() << ":" << std::endl;
        this->ls();
        std::cout << std::endl;
        for (auto file : files)
        {
            if (file->getType() == DIRECTORY)
            {
                Directory *dir = static_cast<Directory *>(file);
                dir->lsRecursive();
            }
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

    bool Directory::isDirContainFile(const std::string& name) const
    {
        for (auto file : files)
        {
            if (file->getName() == name)
                return true;
        }
        return false;
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

    Directory* Directory::findDirInCurrentByName(const std::string& name)
    {
        for (auto file : files)
        {
            if (file->getType() == DIRECTORY && file->getName() == name)
                return static_cast<Directory *>(file);
        }
        return nullptr;
    }

    std::ostream& operator<<(std::ostream& os, const Directory& dir)
    {
        os << (char)dir.getType() << " " << dir.getName() << " " << dir.getPath() << " " << dir.getLastModified();
        return os;
    }

    Directory::~Directory()
    {
        for (auto file : files)
        {
            if (file != nullptr)
            {
                delete file;
                file = nullptr;
            }
        }
    }
}
