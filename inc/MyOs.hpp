#ifndef MYOS_HPP
#define MYOS_HPP

#include <string>
#include <vector>
#include "RegularFile.hpp"
#include "File.hpp"
#include "Directory.hpp"
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
class MyOs
{
    public:
        MyOs();
        ~MyOs();
        //DISK FUNCTIONS

        void                    loadFromDisk();
        void                    saveToDisk();

        //GETTERS

        inline string           getCurrentDirPath() const {return currentDir;}
        inline string           getHomeDir() const {return homeDir;}
        inline string           getRootDir() const {return rootDir;}
        inline vector<File *>   getFiles() const {return files;}
        File*                   getSpesificFile(const string& path) const;
        Directory*              getCurrentDir(const string path);
        Directory*              getCurrentDir();
        string                  getAbsolutePath(const string& path) const;

        //SETTERS

        void                    setCurrentDir(const string& currentDir);
        void                    setHomeDir(const string& homeDir);
        void                    setRootDir(const string& rootDir);

        //ADD ELEMENTS TO VECTOR

        void                    addFile(const File *file);
        void                    deleteFile(const File *file);

        //TIME FUNCTIONS

        string                  getDateAndTime() const;

        //FILE FUNCTIONS

        bool                    isDirExist(const string& path) const;//bynlar directory classında da olabilir
        bool                    isFileExist(const string& path) const; //bir de bu
        string                  handleRelativePath(const string& relativePath) const;
        string                  handleSpecialPath(const string& path) const;
        void                    cd(const string& path);
        void                    cdToAbsolute(const string& path);

        //INPUT FUNCTIONS

        string                  readInput();
        bool                    validateInput(const vector<string>& args);//throws UNKNOWN_CMD
        vector<string >         parseInput(const string& inp);
        vector<string >         splitPath(const string& path, char delimeter) const;

        //CP FUNCTIONS

        void                    cp(const string& src, const string& dest);
        void                    cpFromAbsolute(const string& src, const string& dest);
        void                    cpFromRelative(const string& src, const string& dest);
        void                    cpFileFromMyOs(const string& src);
        void                    cpFileFromRegularOs(const string& src);//throws NO_SUCH_FILE

        //MKDIR FUNCTIONS
        void                    mkdir(const string& arg);

        // OS FUNCTIONS

        void                    run();
        void                    printPrompt() const;
        void                    executeCommand(const vector<string>& args);

    private:
        std::string                 currentDir;
        std::string                 homeDir;
        std::string                 rootDir;
        Directory*                  curDir;
        Directory*                  rtDir;


        //polymorphic vector, it can contain
        //         ->            linkedfiles
        //         ->            directories
        //         ->            regularfiles
        std::vector<File *>        files;
        
};


#endif 