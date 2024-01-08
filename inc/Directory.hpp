#ifndef DIRECTORY_HPP
#define DIRECTORY_HPP

#include "File.hpp"
#include <vector>

using std::string;

class Directory : public File
{
    public:
        //NO PARAMETER CONSTRUCTOR
        Directory() = delete; //My design does not allow to use default constructor

        //COPY CONSTRUCTOR
        Directory(const Directory& other);



        //= OPERATOR OVERLOAD
        Directory&                  operator=(const Directory& other); 

        //PARAMETERIZED CONSTRUCTOR
        Directory(std::string name, std::string path, std::string lastModified);

        //SETTERS
        void                        setFiles(std::vector<File *> files, string lastModified);
        void                        setPrevDir(Directory* prevDir);

        //GETTERS
        inline std::vector<File *>  getFiles() const {return files;}
        inline Directory*           getPrevDir() const {return prevDir;}

        //OVERLOADING OPERATORS
        friend std::ostream&               operator<<(std::ostream& os, const Directory& dir);

        //ADD ELEMENTS TO VECTOR
        void                        addFile(File *file);
        void                        removeFile(File *file);

        //FILE FUNCTIONS
        void                        ls() const override;
        void                        lsRecursive() const;

        //FIND FUNCTIONS
        File*                       findFileInCurrentByName(const std::string& name);
        Directory*                  findDirInCurrentByPath(const std::string& path);
        Directory*                  findDirInCurrentByName(const std::string& name);
        bool                        isDirContainFile(const std::string& name) const;



        //DESTRUCTOR
        ~Directory();   

    private:
        //polymorphic vector, it can contain linkedfiles, directories, regularfiles
        Directory* prevDir;
        std::vector<File *> files;
};

#endif