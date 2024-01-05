#include "File.hpp"

class LinkedFile : public File
{
    public:
        //NO PARAMETER CONSTRUCTOR
        LinkedFile();

        //PARAMETERIZED CONSTRUCTOR
        LinkedFile(std::string name, std::string path, std::string lastModified, File* linkedFile);

        //SETTERS
        inline void             setTheLink(File* linkedFile) {this->linkedFile = linkedFile;}

        //GETTERS
        inline File*            getTheSrcFile() const {return linkedFile;}




    private:
        File* linkedFile;
};