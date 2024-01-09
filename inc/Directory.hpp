#ifndef DIRECTORY_HPP
#define DIRECTORY_HPP

#include "File.hpp"
#include <vector>

using std::string;

namespace FileSystem
{
    class Directory : public File
    {
        public:
            //NO PARAMETER CONSTRUCTOR
            Directory() = delete; //My design does not allow to use default constructor

            //COPY CONSTRUCTOR
            Directory(const Directory& other);



            //= OPERATOR OVERLOAD
            Directory&                  operator=(const Directory& other) = delete;  //My design does not allow to use default constructor

            //PARAMETERIZED CONSTRUCTOR
            Directory(std::string name, std::string path, std::string lastModified);

            //SETTERS
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

            //ITERATOR FUNCTIONS
            class Iterator
            {
                public:
                    Iterator(std::vector<File *>::iterator iterator) : current(iterator) {}

                    Iterator& operator++()
                    {
                        ++current;
                        return *this;
                    }

                    Iterator operator++(int)
                    {
                        Iterator tmp = *this;
                        ++current;
                        return tmp;
                    }

                    bool operator==(const Iterator& other) const
                    {
                        return current == other.current;
                    }

                    bool operator!=(const Iterator& other) const
                    {
                        return current != other.current;
                    }

                    File* operator*() const
                    {
                        return *current;
                    }

                private:
                    std::vector<File*>::iterator current;
            };

            // BEGIN ve END fonksiyonları, başlangıç ve bitiş iterator'larını döndürmek için kullanılabilir.
            Iterator begin()
            {
                return Iterator(files.begin());
            }

            Iterator end()
            {
                return Iterator(files.end());
            }


            //DESTRUCTOR
            ~Directory();   

        private:
            //polymorphic vector, it can contain linkedfiles, directories, regularfiles
            Directory* prevDir;
            std::vector<File *> files;
};
}

#endif