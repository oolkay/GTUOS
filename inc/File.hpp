#ifndef FILE_HPP
#define FILE_HPP

#include <string>
#include <time.h>

#define REGULAR_FILE 'F'
#define LINK         'L'
#define DIRECTORY    'D'
#define NO_SUCH_DIR  "[ERROR] No such directory"
#define DIR_EXIST    "[ERROR] Directory already exists"
#define IS_DIR       "[ERROR] It is a directory"
#define IS_NOT_DIR   "[ERROR] It is not a directory"
#define NO_SUCH_FILE "[ERROR] No such file"
#define SAME_FILE    "[ERROR] The file is already exist"
#define SAME_DIR     "[ERROR] You can not copy directory to itself"

//NAMESPACE UNUTMA
//ABSTRACT  UNUTMA

//THIS CLASS IS THE 'INTERFACE' FOR THE FILES
//SUCH AS 'RegulerFile', 'Directory', 'Link'
class File
{
    public:
        //NO PARAMETER CONSTRUCTOR
        File() = default;
        
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