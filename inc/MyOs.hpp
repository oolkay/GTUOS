#ifndef MYOS_HPP
#define MYOS_HPP

#include <string>
#include <vector>
#include "RegularFile.hpp"
#include "File.hpp"
#include "Directory.hpp"
#include "Disk.hpp"
// #include "Directory.hpp"
// #include "Link.hpp"

using std::string;
using std::vector;
using std::stringstream;

#define UNKNOWN_CMD  "[ERROR] Command not found"
#define MISSING_ARG  "[ERROR] Missing argument"
#define EXTRA_ARG    "[ERROR] Too many arguments"


//abstract olabilir?
//THIS CLASS IS THE INTERFACE FOR THE OS
//static olabilir!é!!!!!!!
class MyOs
{
    public:
        MyOs();
        ~MyOs();

        //GETTERS

        File*                   getSpesificFile(const string& path);
        Directory*              getCurrentDir();
        string                  getAbsolutePath(const string& path) const;
        inline std::size_t      getDiskSize() const {return diskSize;}

        //SETTERS
    

        //TIME FUNCTIONS

        string                  getDateAndTime() const;

        //FILE FUNCTIONS

        char                    isFileExistInMyOs(const string& path); //bir de bu
        bool                    isFileExistInRegOs(const string& path);
        string                  handleRelativePath(const string& relativePath) const;
        void                    cd(const string& path);
        void                    cdToGivenPath(const string& path);

        //INPUT FUNCTIONS

        string                  readInput();
        bool                    validateInput(const vector<string>& args);//throws UNKNOWN_CMD
        vector<string >         parseInput(const string& inp);
        vector<string >         splitPath(const string& path, char delimeter) const;

        //CP FUNCTIONS

        void                    cp(const string& src, const string& dest);
        void                    cpFileFromMyOs(const string& src);
        void                    cpFileFromRegularOs(const string& src);//throws NO_SUCH_FILE

        //MKDIR FUNCTIONS
        void                    mkdir(const string& arg);

        // OS FUNCTIONS

        void                    run();
        void                    printPrompt() const;
        void                    executeCommand(const vector<string>& args);

        // DISK FUNCTIONS
        void                    readDisk();
        void                    writeDisk(File* data); //inyt döndürebilir
        void                    loadDirectory(const string& name, const string& path, const string& lastModified);
        void                    loadRegularFile(const string& name, const string& path, const string& lastModified, const string& content, const size_t& size);
        void                    loadRegularFileContentAndSize(std::string& content, size_t& size, std::ifstream &file);

    private:
        Directory*                  curDir;
        Directory*                  rootDir;
        std::size_t                 diskSize;


        //polymorphic vector, it can contain
        //         ->            linkedfiles
        //         ->            directories
        //         ->            regularfiles
        std::vector<File *>        files;
        
};


#endif 