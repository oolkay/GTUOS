#ifndef LINKEDFILE_HPP
#define LINKEDFILE_HPP

#include "File.hpp"


namespace FileSystem
{
    class LinkedFile : public File
    {
        public:
            //NO PARAMETER CONSTRUCTOR
            LinkedFile() = delete; //My design does not allow to use default constructor

            //COPY CONSTRUCTOR
            LinkedFile(const LinkedFile& other); //My design does not allow to use copy constructor

            //= OPERATOR OVERLOAD
            LinkedFile&             operator=(const LinkedFile& other) = default; //My design does not allow to use = operator
            
            ~LinkedFile();

            //PARAMETERIZED CONSTRUCTOR
            LinkedFile(std::string name, std::string path, std::string lastModified,
                std::string linkName, std::string linkPath, File* linkedFile);

            //SETTERS
            inline void             setTheLink(File* linkedFile) {this->linkedFile = linkedFile;}

            //GETTERS
            inline File*            getLinkedFile() const {return linkedFile;}
            inline std::string      getLinkedFileName() const {return linkedFileName;}
            inline std::string      getLinkedFilePath() const {return linkedFilePath;}
            
            // OPERATOR OVERLOADINGS
            friend std::ostream&    operator<<(std::ostream& os, const LinkedFile& file);

            //ls FUNCTION
            void                    ls() const override;
            void                    cat() const override;

        private:
            File*       linkedFile;
            std::string linkedFileName;
            std::string linkedFilePath;
    };
}

#endif