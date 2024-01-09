#ifndef MYOS_HPP
#define MYOS_HPP

#include <string>
#include <vector>
#include "RegularFile.hpp"
#include "File.hpp"
#include "Directory.hpp"
#include "LinkedFile.hpp"

using std::string;
using std::vector;
using std::stringstream;

namespace OlkayOS
{
    using namespace FileSystem;
    // STATIC CLASS
    // NO OBJECT CREATION

    class MyOs
    {
        public:
            MyOs() = delete;
            ~MyOs() = delete;
            MyOs(const MyOs& other) = delete;
            MyOs& operator=(const MyOs& other) = delete;
            

            //GETTERS

            static inline std::size_t      getDiskSize()  {return diskSize;}

            //SETTERS
        
            //PATH FUNCTIONS

            static string                  handleRelativePath(const string& relativePath);
            static vector<string >         splitPath(const string& path, char delimeter);
            static string                  getAbsolutePath(const string& path);
            static Directory*              getParentDir(const string& path);

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
            static void                    cpFileFromMyOs(const string& src, const string& destName);
            template<class T>
            static T*                      createCopyFile(T* src, Directory *prevDir, const string& destName);
            static void                    generateCopyFile(File *src, Directory *prevDir, const string& destName);
            static void                    cpFileFromRegularOs(const string& src, const string& destName);//throws NO_SUCH_FILE
            static Directory*              cpDirRecursive(Directory *dir, Directory *prevDir, const string& destName);

            //MKDIR FUNCTIONS

            static void                    mkdir(const string& arg);

            // CD FUNCTIONS

            static void                    cd(const string& path);
            static void                    cdToGivenPath(const string& path);

            // LS FUNCTIONS

            static void                    ls(const vector<string >& args);

            // CAT FUNCTIONS
            static void                    cat(const vector<string >& args);

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
            static void                    updateDisk(std::ofstream& ofs, Directory* curDir);
            static void                    updateDiskHelper();
            static void                    updateTheLinks(const Directory* dir);
            static void                    loadDirectory(const string& name, const string& path, const string& lastModified);
            static void                    loadRegularFile(const string& name, const string& path, const string& lastModified, const string& content, const size_t& size);
            static void                    loadRegularFileContent(std::string& content, std::ifstream &file);
            static void                    loadLinkedFile(const string& name, const string& path, const string& lastModified, 
                                                            const string& linkName, const string& linkPath, File* linkedFile);

        private:
            static Directory*                  curDir;
            static Directory*                  rootDir;
            static std::size_t                 diskSize;
            
    };
}


#endif 