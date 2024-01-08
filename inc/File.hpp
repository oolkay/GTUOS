#ifndef FILE_HPP
#define FILE_HPP

#include <string>
#include <time.h>
#include "Defines.hpp"

//NAMESPACE UNUTMA
//ABSTRACT  UNUTMA

//THIS CLASS IS THE 'INTERFACE' FOR THE FILES
//SUCH AS 'RegulerFile', 'Directory', 'Link'
class File
{
    public:
        //NO PARAMETER CONSTRUCTOR
        File() = delete; //My design does not allow to use default constructor

        //COPY CONSTRUCTOR
        File(const File& other) = default; //default is enough

        //= OPERATOR OVERLOAD
        File&               operator=(const File& other) = default; //default is enough

        //PARAMETERIZED CONSTRUCTOR
        File(int type, std::string name, std::string path, std::string lastModified);

        //SETTERS
        void                setType(int type);//throw(std::invalid_argument);
        void                setName(std::string name);//throw(std::invalid_argument);
        void                setPath(std::string path);//throw(std::invalid_argument);
        void                setLastModified(std::string lastModified);//throw(std::invalid_argument);

        //GETTERS
        inline char         getType() const {return type;}
        inline std::string  getName() const {return name;}
        inline std::string  getPath() const {return path;}
        std::string         getPathWorkingDirectory() const;
        inline std::string  getLastModified() const {return lastModified;}


        //FILE FUNCTIONS
        virtual void        ls() const; //pure virtual?
        virtual void        cat() const; //iterator kullanilabilir
        // virtual void        cd(const std::string& path);

        //OVERLOADING OPERATORS
        bool               operator==(const File& other) const;

        //DESTRUCTOR
        virtual             ~File() = 0;

    protected:
        char                type;
        std::string         name;
        std::string         path;
        std::string         lastModified;
        // std::string content; gerek yok gibi
        /*TODO: MONTH*/

};

#endif 