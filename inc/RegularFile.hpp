#ifndef REGULAR_FILE_HPP
#define REGULAR_FILE_HPP

#include "File.hpp"

class RegularFile : public File
{
    public:
        //NO PARAMETER CONSTRUCTOR
        RegularFile();

        //PARAMETERIZED CONSTRUCTOR
        // lastModified default olarak alinabilir kendi halledebilir içeride
        RegularFile(std::string name, std::string path, std::string lastModified, std::string content = "", size_t size = 0);

        //SETTERS
        void                    setContent(std::string content);
        void                    setSize(size_t size);

        //GETTERS
        inline std::string      getContent() const {return content;}
        inline size_t           getSize() const {return size;}

        //OVERLOADING OPERATORS
        friend std::ostream&    operator<<(std::ostream& os, const RegularFile& regFile);

        //FILE FUNCTIONS
        void                    ls() const override;
        void                    cat() const override;

        //DESTRUCTOR
        ~RegularFile();

    private:
        std::string content;
        size_t      size;
};

#endif