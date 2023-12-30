#include "../inc/MyOs.hpp"
#include <sstream>
#include <iostream>
#include <fstream>
#include <istream>
#include <stdexcept>
#include <chrono>
#include <ctime>

using std::string;
using std::vector;
using std::stringstream;
using std::cout;
using std::endl;

MyOs::MyOs()
{
    rtDir = new Directory("/", "/", getDateAndTime());
    rtDir->addFile(new Directory(".", "/.", getDateAndTime()));
    curDir = rtDir;
}

MyOs::~MyOs()
{
    for (auto& file : files)
        delete file;
}

void MyOs::setCurrentDir(const string& currentDir)
{
    if (!isDirExist(currentDir))
        throw std::runtime_error(NO_SUCH_DIR);
    this->currentDir = currentDir;
}

// RUN FUNCTION IS THE MAIN LOOP OF THE OS
// IT READS INPUT, VALIDATES IT AND CALLS THE EXECUTER
void MyOs::run()
{

    string          inp;
    vector<string>  args;
    // CONSTRUCTORDA EKLEMEK GÜZEL FİKİR
    // mkdir("zart");
    // files.push_back(new RegularFile("file1", "/home/omer/zart/file1", getDateAndTime(), "contentcontent"));
    while (inp != "exit")
    {
        printPrompt();
        inp = readInput();
        if (!inp.empty())
        {
            args = parseInput(inp);
            try
            {
                validateInput(args);
                executeCommand(args);
            }
            catch (std::exception& e)
            {
                std::cout << e.what() << std::endl;
                continue;
            }
        }
    }
}

// READS INPUT FROM USER
string MyOs::readInput()
{
    string  inp;
    getline(std::cin, inp);
    return inp;
}

// VALIDATES THE INPUT// Şu anki zamanı elde et
// THROWs UNKNOWN_CMD, MISSING_ARG, EXTRA_ARG
bool MyOs::validateInput(const vector<string>& args)
{
    string  cmd;
    
    if (args.size() == 0)
        return true;
    cmd = args[0];
    if (args.size() > 0)
    {
        if (!(cmd == "ls" || cmd == "mkdir" || cmd == "exit"
                || cmd == "cd" || cmd == "cp" || cmd == "cat" || cmd == "pwd"))
        {
            throw std::runtime_error(UNKNOWN_CMD);
            return false;
        }
        if (args.size() >= 4)
        {
            throw std::runtime_error(EXTRA_ARG);
            return false;
        }
        if ((cmd == "mkdir" || cmd == "cat") && args.size() < 2)
        {
            throw std::runtime_error(MISSING_ARG);
            return false;
        }
        else if (cmd == "cp" && args.size() < 3)
        {
            throw std::runtime_error(MISSING_ARG);
            return false;
        }
    }
    return true;
}

// PARSES THE INPUT, args[0] IS THE COMMAND, REST ARE ARGUMENTS
vector<string> MyOs::parseInput(const string& inp)
{
    vector<string>  args;
    stringstream    ss(inp);
    string          word;

    while (ss >> word)
        args.push_back(word);
    return args;
}

vector<string> MyOs::splitPath(const string& path, char delimeter) const
{
    vector<string>  paths;
    stringstream    ss(path);
    string          word;

    while (getline(ss, word, delimeter))
        if (!word.empty())
            paths.push_back(word);
    return paths;
}

// PRINTS THE PROMPT
void MyOs::printPrompt() const
{
    std::cout << "> ";
}

// EXECUTES THE COMMAND
void MyOs::executeCommand(const vector<string>& args)
{
    string  cmd;

    cmd = args[0];
    if (cmd == "ls")
    {
        curDir->ls();
    }
    else if (cmd == "mkdir")
    {
        mkdir(args[1]);
    }
    else if (cmd == "cd")
    {
        if (args.size() == 1)
            cd("");
        else
            cd(args[1]);
    }
    else if (cmd == "cp")
    {
        cp(args[1], args[2]);
    }
    else if (cmd == "cat")
    {
        File*   file = getSpesificFile(args[1]);
        if (file == nullptr)
            throw std::runtime_error(NO_SUCH_FILE);
        if (file->getType() == REGULAR_FILE)
            file->cat();
        else
            throw std::runtime_error(IS_DIR);
    }
    else if (cmd == "pwd")
    {
        string path = curDir->getPath();
        cout << path << endl;
    }
}

// CHECKS IF THE DIRECTORY EXISTS
bool MyOs::isDirExist(const string& path) const
{
    for (const auto& file : curDir->getFiles())
    {
        if (file->getPath() == path)
            return true;
    }
    return false;
}

// currentDir + path    = newPath
// /home/omer + Desktop = /home/omer/Desktop
string MyOs::handleRelativePath(const string& relativePath) const
{
    if (curDir->getPath() == "/")
        return curDir->getPath() + relativePath;
    else
        return curDir->getPath() + "/" + relativePath;
}

// Changes the current directory
void MyOs::cd(const string& path)
{
    // special paths
    if (path.empty())
        curDir = rtDir;
    else if (path == "/")
        curDir = rtDir;
    else if (path == ".." && curDir->getPath() != "/")
        curDir = curDir->getPrevDir();

    // cd /home/omer -> absolute path
    else if (path[0] == '/')
        cdToAbsolute(path);
    // relative path
    else
    {
        string absolutePath = handleRelativePath(path);
        if (isDirExist(absolutePath))
            curDir = curDir->findDirInCurrentByPath(absolutePath);
        else
            throw std::runtime_error(NO_SUCH_DIR);
    }
}

void MyOs::cdToAbsolute(const string& path)
{
    vector<string>  paths = splitPath(path, '/');
    Directory*      tmpDirCur = curDir;
    curDir = rtDir;
    for (unsigned int i = 0; i < paths.size(); i++)
    {
        if (paths[i] == "..")
        {
            if (curDir->getPath().find_last_of("/") == 0)
                curDir = rtDir;
            else
                curDir = curDir->getPrevDir();
        }
        else if (paths[i] != ".")
        {
            string absolutePath = handleRelativePath(paths[i]);
            if (isDirExist(absolutePath))
                curDir = curDir->findDirInCurrentByPath(absolutePath);
            else
            {
                curDir = tmpDirCur;
                throw std::runtime_error(NO_SUCH_DIR);
            }
        }
    }
}

string MyOs::handleSpecialPath(const string& path) const
{
    if (path == ".")
        return (this->currentDir);
    if (path == "..")
    {
        if (this->currentDir == "/")
            return (this->currentDir);
        if (this->currentDir.find_last_of("/") == 0)
            return ("/");
        return (this->currentDir.substr(0, this->currentDir.find_last_of("/")));
    }
    // cd /    -> back to the root
    if (path == "/")
        return (path);
    
    // no argument of cd
    return ("/");
}

// Checks if the file exists in regularOS or myOS
// returns 1 if exists in regularOS and 0 if not exists 
bool MyOs::isFileExist(const string& path) const
{
    std::ifstream   ifs;
    std::string     absolutePath;

    absolutePath = getAbsolutePath(path);
  
    // check if exists in regularOS
    ifs.open(absolutePath);
    if (ifs.is_open())
    {
        ifs.close();
        return true;
    }
    return false;
}

// RETURNS THE GIVEN FILE IF EXISTS IN MY OS
// IF NOT RETURNS NULLPTR
File* MyOs::getSpesificFile(const string& path) const
{
    string absolutePath = getAbsolutePath(path);
    for (const auto& file : files)
    {
        if (file->getPath() == absolutePath)
            return file;
    }
    return nullptr;
}

// COPY THE FILE FROM MY OS TO MY OS(CURRENT DIR)
// THROWS NO_SUCH_FILE, SAME_FILE
void MyOs::cpFileFromMyOs(const string& src)
{
    //absolute path
    if (src[0] == '/')
    {
        cpFromAbsolute(src, ".");
    }




    // Directory* dir = curDir;
    // File*   file = getSpesificFile(src);
    // if (file->getType() == REGULAR_FILE)
    // {
    //     if (file->getPath() == currentDir)
    //         throw std::runtime_error(SAME_FILE);
    //     else
    //     {
    //         //last modif farklı olcak
    //         RegularFile *srcFile = dynamic_cast<RegularFile*>(file);
    //         File *copyFile = new RegularFile(file->getName(), currentDir,
    //             getDateAndTime(), srcFile->getContent(), srcFile->getSize());
    //         dir->addFile(copyFile);
    //         // files.push_back(copyFile);
    //     }
    // }
    // else if (file->getType() == DIRECTORY)
    // {
    //     File *copyDir = new Directory(*(dynamic_cast<Directory*>(file)));
    //     dir->addFile(copyDir);
    //     // files.push_back(copyDir);
    // }
    // else if (file->getType() == LINK)
    // {

    // }

}

void MyOs::cpFromAbsolute(const string& src, const string& dest)
{
    string      srcDir = src.substr(0, src.find_last_of("/"));
    string      srcFile = src.substr(src.find_last_of("/") + 1);
    Directory*  tmpCurDir = curDir;
    File*       file;
    (void)dest;

    if (srcDir == curDir->getPath())
    {
        cerr << SAME_FILE << endl;
        return;
    }
    try
    {
        cd(srcDir);
        file = curDir->findFileInCurrentByName(srcFile);
        cd(tmpCurDir->getPath());
        if (file != nullptr && file->getType() == REGULAR_FILE)
        {
            RegularFile *sourceFile = new RegularFile(*(dynamic_cast<RegularFile*>(file)));
            string time = getDateAndTime();
            curDir->setLastModified(time);
            File *copyFile = new RegularFile(sourceFile->getName(), curDir->getPath()+"/"+file->getName(),
                time, sourceFile->getContent(), sourceFile->getSize());
            curDir->addFile(copyFile);
        }
        curDir = tmpCurDir;
    }
    catch(const std::exception& e)
    {
        curDir = tmpCurDir;
        std::cerr << e.what() << '\n';
    }

}

// COPY THE FILE FROM REGULAR OS TO MY OS(CURRENT DIR)
// THROWS NO_SUCH_FILE


//cp /home/omer yapınca garip bir şekilde kopyaladı ona dikkat
void MyOs::cpFileFromRegularOs(const string& src)
{
    std::ifstream   ifs;
    size_t          size = 0;
    string          time;

    ifs.open(src);
    if (ifs.is_open())
    {
        std::string     content;
        while (ifs.good())
        {
            char        ch;
            while (ifs.get(ch))
            {
                content += ch;
                size++;
            }
        }
        ifs.close();
        time = getDateAndTime();
        string fileName = src.substr(src.find_last_of("/") + 1);
        File *copyFile = new RegularFile(fileName, currentDir+"/"+fileName,
            time, content, size);
        curDir->addFile(copyFile);
        curDir->setLastModified(time);
    }
    else
        throw std::runtime_error(NO_SUCH_FILE);
    
}

// Copies the file src to dest
void MyOs::cp(const string& src, const string& dest)
{
    int    isExist;

    isExist = isFileExist(src);
    (void)dest;
    // IN MY OS
    if (isExist == 1)
        cpFileFromRegularOs(src);
    // IN REGULAR OS
    else
        cpFileFromMyOs(src);
}

// RETURNS THE ABSOLUTE PATH OF THE GIVEN PATH
string MyOs::getAbsolutePath(const string& path) const
{
    if (path[0] == '/')
        return path;
    return handleRelativePath(path);
}

string MyOs::getDateAndTime() const
{
    // Şu anki zamanı elde et
    auto current_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    // C tarih yapısına dönüştür
    struct tm* time_info = std::localtime(&current_time);

    // Tarih ve saat bilgisini bir string olarak oluştur
    char buffer[20]; // "AY GÜN SAAT\0" için yeterli boyutta bir buffer
    std::strftime(buffer, sizeof(buffer), "%b %d %H:%M", time_info);

    return std::string(buffer);
}

void MyOs::mkdir(const string& arg)
{
    string  absolutePath;
    if (curDir->getPath() == "/")
        absolutePath = curDir->getPath() + arg;
    else
        absolutePath = curDir->getPath() + "/" + arg;
    if (isDirExist(absolutePath))
        throw std::runtime_error(DIR_EXIST);
    Directory *newDir = new Directory(arg, absolutePath, getDateAndTime());
    newDir->addFile(new Directory(".", absolutePath+"/.", getDateAndTime()));
    newDir->addFile(new Directory("..", absolutePath+"/..", getDateAndTime()));
    newDir->setPrevDir(curDir);
    curDir->addFile(newDir);
    // files.push_back(new Directory(arg, absolutePath, getDateAndTime()));
    // files.push_back(new Directory(".", absolutePath+"/.", getDateAndTime()));
    // files.push_back(new Directory("..", absolutePath+"/..", getDateAndTime()));
}

Directory* MyOs::getCurrentDir()
{
    return curDir;
}

 Directory* MyOs::getCurrentDir(const string path) 
{
    (void)path;
    for (const auto& file : files)
    {
        if (file->getDir() == currentDir)
            return (dynamic_cast< Directory*>(file));
    }
    return nullptr;
}
