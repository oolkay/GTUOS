#ifndef DIRECTORY_HPP
#define DIRECTORY_HPP

#include "File.hpp"
#include <vector>

class Directory : public File
{
    public:
        //NO PARAMETER CONSTRUCTOR
        Directory();

        //PARAMETERIZED CONSTRUCTOR
        Directory(std::string name, std::string path, std::string lastModified);

        //SETTERS
        void                        setFiles(std::vector<File *> files);
        void                        setPrevDir(Directory* prevDir);

        //GETTERS
        inline std::vector<File *>  getFiles() const {return files;}
        inline Directory*           getPrevDir() const {return prevDir;}

        //OVERLOADING OPERATORS
        friend std::ostream&        operator<<(std::ostream& os, const Directory& directory);

        //ADD ELEMENTS TO VECTOR
        void                        addFile(File *file);

        //FILE FUNCTIONS
        void                        ls() const override;

        //FIND FUNCTIONS
        File*                       findFileInCurrentByName(const std::string& name);
        Directory*                  findDirInCurrentByPath(const std::string& path);

        //DESTRUCTOR
        ~Directory();   

    private:
        //polymorphic vector, it can contain linkedfiles, directories, regularfiles
        Directory* prevDir;
        std::vector<File *> files;
};

#endif