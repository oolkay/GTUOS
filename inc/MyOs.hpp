#ifndef MYOS_HPP
#define MYOS_HPP

#include <string>
#include <vector>
#include "RegularFile.hpp"
#include "File.hpp"
#include "Directory.hpp"
#include "Disk.hpp"
#include "LinkedFile.hpp"
// #include "Directory.hpp"
// #include "Link.hpp"

using std::string;
using std::vector;
using std::stringstream;

#define UNKNOWN_CMD  "[ERROR] Command not found"
#define MISSING_ARG  "[ERROR] Missing argument"
#define EXTRA_ARG    "[ERROR] Too many arguments"
#define CAN_NOT_REMOVE "[ERROR] You can not remove"
#define CAN_NOT_LINK "[ERROR] The linked file is already exist"

#define USER_NAME    "omer"
#define HOST_NAME    "olkayOS"

#define DEFAULT "\033[0;39m"
#define GRAY "\033[0;90m"
#define RED "\033[0;91m"
#define GREEN "\033[0;92m"
#define YELLOW "\033[0;93m"
#define BLUE "\033[0;94m"
#define MAGENTA "\033[0;95m"
#define CYAN "\033[0;96m"
#define WHITE "\033[0;97m"

// STATIC CLASS
// NO OBJECT CREATION
class MyOs
{
    public:
        MyOs();
        ~MyOs();
        

        //GETTERS

        static inline std::size_t      getDiskSize()  {return diskSize;}

        //SETTERS
    
        //PATH FUNCTIONS

        static string                  handleRelativePath(const string& relativePath);
        static vector<string >         splitPath(const string& path, char delimeter);
        static string                  getAbsolutePath(const string& path);

        //TIME FUNCTIONS

        static string                  getDateAndTime();

        //FILE FUNCTIONS

        static char                    isFileExistInMyOs(const string& path); //bir de bu
        static bool                    isFileExistInRegOs(const string& path);
        static File*                   getSpesificFile(const string& path);
        static Directory*              getCurrentDir();

        //INPUT FUNCTIONS

        static string                  readInput();
        static bool                    validateInput(const vector<string>& args);//throws UNKNOWN_CMD
        static vector<string >         parseInput(const string& inp);

        //CP FUNCTIONS

        static void                    cp(const string& src, const string& dest);
        static void                    cpFileFromMyOs(const string& src);
        static void                    generateCopyFile(File *src);
        static void                    cpFileFromRegularOs(const string& src);//throws NO_SUCH_FILE

        //MKDIR FUNCTIONS

        static void                    mkdir(const string& arg);

        // CD FUNCTIONS

        static void                    cd(const string& path);
        static void                    cdToGivenPath(const string& path);

        // OS FUNCTIONS

        static void                    init();
        static void                    run();
        static void                    printPrompt();
        static void                    executeCommand(const vector<string>& args);
        static void                    freeTempMemory();

        // LINK FUNCTIONS
        static void                    ln(const vector<string >& args);

        // RM FUNCTIONS
        static void                    rm(const vector<string >& args);
        static void                    rmFile(File* file, Directory* parentDir);
        static void                    rmRecursive(File *file, Directory* parentDir);

        // DISK FUNCTIONS
        static void                    readDisk();
        static void                    writeDisk(File* data); //inyt döndürebilir
        static void                    updateDisk();
        static void                    loadDirectory(const string& name, const string& path, const string& lastModified);
        static void                    loadRegularFile(const string& name, const string& path, const string& lastModified, const string& content, const size_t& size);
        static void                    loadRegularFileContent(std::string& content, std::ifstream &file);

    private:
        static Directory*                  curDir;
        static Directory*                  rootDir;
        static std::size_t                 diskSize;
        
};


#endif 