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

void Directory::setFiles(std::vector<File *> files, string lastModified)
{
    //deep copy
    for (auto file : files)
    {
        string name = file->getName();
        string path = file->getPath();
        if (file->getType() == REGULAR_FILE)
        {
            RegularFile *f = dynamic_cast<RegularFile *>(file);
            this->files.push_back(new RegularFile(name, path, lastModified, 
                        f->getContent(), f->getSize()));
        }
        else if (file->getType() == DIRECTORY)
            this->files.push_back(new Directory(name, path, lastModified));
        // else if (file->getType() == LINK)
        //     this->files.push_back(new LinkedFile(*static_cast<LinkedFile *>(file)));
    }
}

void Directory::setPrevDir(Directory* prevDir)
{
    this->prevDir = prevDir;
}

void Directory::addFile(File *file)
{
    files.push_back(file);
    setLastModified(file->getLastModified());
    findDirInCurrentByName(".")->setLastModified(file->getLastModified());
}

void Directory::removeFile(File *file)
{
    for (auto it = files.begin(); it != files.end(); ++it)
    {
        if (*it == file)
        {
            cout << "File " << file->getName() << " removed" << endl;
            files.erase(it);
            delete file;
            return ;
        }
    }
}

void Directory::ls() const
{
    for (auto file : files)
    {
        if (file->getType() == REGULAR_FILE || file->getType() == LINK)
            file->ls();
        else
        {
            std::cout   << static_cast<char>(file->getType()) << " "
                << file->getName() << "      "
                << file->getLastModified() << std::endl;
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
        if (file->getType() == DIRECTORY && 
            file->getName() != "." && file->getName() != "..")
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
