#ifndef LINKEDFILE_HPP
#define LINKEDFILE_HPP

#include "File.hpp"

#define NO_LINK "The linked file is not exist"

class LinkedFile : public File
{
    public:
        //NO PARAMETER CONSTRUCTOR
        LinkedFile();
        
        ~LinkedFile();

        //PARAMETERIZED CONSTRUCTOR
        LinkedFile(std::string name, std::string path, std::string lastModified, File* linkedFile);

        //SETTERS
        inline void             setTheLink(File* linkedFile) {this->linkedFile = linkedFile;}

        //GETTERS
        inline File*            getLinkedFile() const {return linkedFile;}

        //ls FUNCTION
        void                    ls() const override;
        void                    cat() const override;

    private:
        File* linkedFile;
};

#endif