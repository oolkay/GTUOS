#include "../inc/MyOs.hpp"
#include <sstream>
#include <iostream>
#include <fstream>
#include <istream>
#include <stdexcept>
#include <chrono>
#include <ctime>
#include <stdexcept>

using std::string;
using std::vector;
using std::stringstream;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;

Directory* MyOs::rootDir = nullptr;
Directory* MyOs::curDir = nullptr;
size_t     MyOs::diskSize = 0;

// MyOs::~MyOs()
// {
//     for (auto& file : files)
//         delete file;
// }

void MyOs::init()
{
    try
    {
        readDisk();
        if (rootDir == nullptr)
        {
            rootDir = new Directory("/", "/", getDateAndTime());
            rootDir->addFile(new Directory(".", "/.", getDateAndTime()));
            rootDir->setPrevDir(nullptr);
            writeDisk(rootDir);
        }
        curDir = rootDir;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        exit (-1);
    }
}

void MyOs::freeTempMemory()
{
    if (rootDir != nullptr)
        delete rootDir;
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
    freeTempMemory();
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
        else if ((cmd == "mkdir" || cmd == "cat") && args.size() > 2)
        {
            throw std::runtime_error(EXTRA_ARG);
            return false;
        }
        else if (cmd == "cp" && args.size() < 3)
        {
            throw std::runtime_error(MISSING_ARG);
            return false;
        }
        else if (cmd == "ls")
        {
            if (args.size() > 2)
                throw std::runtime_error(EXTRA_ARG);
            if (args.size() == 2 && args[1] != "-R")
                throw std::runtime_error(UNKNOWN_CMD);
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

vector<string> MyOs::splitPath(const string& path, char delimeter)
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
void MyOs::printPrompt()
{
    std::cout << CYAN << USER_NAME << BLUE << "@" <<HOST_NAME
                <<"   " <<MAGENTA << curDir->getPath() << "> " << DEFAULT;
}

// EXECUTES THE COMMAND
void MyOs::executeCommand(const vector<string>& args)
{
    string  cmd;

    cmd = args[0];
    if (cmd == "ls")
    {
        if (args.size() > 1 && args[1] == "-R")
            curDir->lsRecursive();
        else
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
        string fileToCat = args[1];
        if (!fileToCat.empty())
        {
            File* file = getSpesificFile(fileToCat);
            if (file != nullptr && file->getType() == REGULAR_FILE)
                dynamic_cast<RegularFile *>(file)->cat();
            else if (file == nullptr)
                std::cerr << NO_SUCH_FILE << endl;
            else if (file->getType() == DIRECTORY)
                std::cerr << IS_DIR << endl;
        }
    }
    else if (cmd == "pwd")
    {
        string path = curDir->getPath();
        cout << path << endl;
    }
}

// currentDir + path    = newPath
// /home/omer + Desktop = /home/omer/Desktop
string MyOs::handleRelativePath(const string& relativePath)
{
    // if current directory is root directory
    if (curDir->getPath() == "/")
        return ("/" + relativePath);
    else
        return curDir->getPath() + "/" + relativePath;
}

// Changes the current directory
void MyOs::cd(const string& path)
{
    // special paths
    if (path.empty())
        curDir = rootDir;
    else if (path == "/")
        curDir = rootDir;
    else if (path == ".." && curDir->getPath() != "/")
        curDir = curDir->getPrevDir();
    cdToGivenPath(path);
}

void MyOs::cdToGivenPath(const string& path)
{
    //a/b/c -> a   b   c
    vector<string>  paths = splitPath(path, '/');
    Directory*      tmpDirCur = curDir;
    if (path[0] == '/')
        curDir = rootDir;
    for (unsigned int i = 0; i < paths.size(); i++)
    {
        if (paths[i] == "..")
        {
            if (curDir->getPath().find_last_of("/") == 0)
                curDir = rootDir;
            else
                curDir = curDir->getPrevDir();
        }
        else if (paths[i] != ".")
        {
            if (isFileExistInMyOs(paths[i]) == DIRECTORY)
                curDir = curDir->findDirInCurrentByName(paths[i]);
            else
            {
                curDir = tmpDirCur;
                throw std::invalid_argument(NO_SUCH_DIR);
            }
        }
    }
}

//Checks whether the file exist in my os or not
//all kind of file types are valid(dir,reg,link)
char MyOs::isFileExistInMyOs(const string& path)
{
    File *f = getSpesificFile(path);
    if (f == nullptr)
        return (0);
    else
        return f->getType();
}

bool MyOs::isFileExistInRegOs(const string& path)
{
    std::ifstream   ifs;
    ifs.open(path);
    if (ifs.good())
    {
        ifs.close();
        return true;
    }
    return false;
}

// RETURNS THE GIVEN FILE IF EXISTS IN MY OS
// IF NOT RETURNS NULLPTR
File* MyOs::getSpesificFile(const string& path)
{
    string absolutePath     = getAbsolutePath(path);
    if (absolutePath == "/")
        return rootDir;
    string pwd              = absolutePath.substr(0, absolutePath.find_last_of("/"));
    string name             = absolutePath.substr(absolutePath.find_last_of("/") + 1);
    Directory* tempCurDir   = curDir;
    //path /a.c gibi bir şey ise yani root directoryde ise
    //pwd boş oluyor
    if (!pwd.empty())
        cd(pwd);
    else
        curDir = rootDir;

    vector<File *> files = curDir->getFiles();
    for (const auto& file : files)
    {
        if (file->getName() == name)
        {
            curDir = tempCurDir;
            return file;
        }
    }
    curDir = tempCurDir;
    return nullptr;
}

// COPY THE FILE FROM MY OS TO MY OS(CURRENT DIR)
// THROWS NO_SUCH_FILE, SAME_FILE
void MyOs::cpFileFromMyOs(const string& src)
{
    string name;
    string path;
    string content;
    string time = getDateAndTime();
    File *file  = getSpesificFile(src);
    if (file->getType() == REGULAR_FILE)
    {
        RegularFile *srcFile = dynamic_cast<RegularFile*>(file);
        name = srcFile->getName();
        path = curDir->getPath() + "/" + name;
        content = srcFile->getContent();
        File* copyFile = new RegularFile(name, path, time, content, srcFile->getSize());
        curDir->addFile(copyFile);
        curDir->findDirInCurrentByName(".")->setLastModified(time);
        writeDisk(copyFile);
    }
    // else if (file->getType() == LINK)
    // {

    // }

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
        string path;
        if (curDir->getPath() == "/")
            path = "/"+fileName;
        else
            path = curDir->getPath() + "/" + fileName;
        File *copyFile = new RegularFile(fileName, path,
            time, content, size);
        curDir->addFile(copyFile);
        curDir->setLastModified(time);
        curDir->findDirInCurrentByName(".")->setLastModified(time);
        writeDisk(copyFile);
    }
    else
        throw std::runtime_error(NO_SUCH_FILE);
    
}

// Copies the file src to dest
void MyOs::cp(const string& src, const string& dest)
{
    int    isExist = 0;
    (void)dest;
    if (isFileExistInRegOs(src) == true)
        cpFileFromRegularOs(src);
    else
    {
        isExist = isFileExistInMyOs(src);
        if (isExist > 0)
        {
            if (src.find("/") != std::string::npos)
                cpFileFromMyOs(src);
            else
                throw std::runtime_error(SAME_FILE);
        }
        else
            throw::std::runtime_error(NO_SUCH_FILE);
    }
    // IN REGULAR OS
}

// RETURNS THE ABSOLUTE PATH OF THE GIVEN PATH
// IF THE PATH IS ALREADY ABSOLUTE RETURNS ITSELF
string MyOs::getAbsolutePath(const string& path)
{
    if (path[0] == '/')
        return path;
    return handleRelativePath(path);
}

string MyOs::getDateAndTime()
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
    if (isFileExistInMyOs(absolutePath))
        throw std::runtime_error(DIR_EXIST);
    Directory *newDir = new Directory(arg, absolutePath, getDateAndTime());
    newDir->addFile(new Directory(".", absolutePath+"/.", getDateAndTime()));
    newDir->setPrevDir(curDir);
    newDir->addFile(new Directory("..", absolutePath+"/..", curDir->getLastModified()));
    curDir->addFile(newDir);
    curDir->findDirInCurrentByName(".")->setLastModified(getDateAndTime());
    writeDisk(newDir);
}


void MyOs::readDisk()
{
    ifstream    disk;
    string      line;
    string      fileName;
    char        fileType;
    string      filePath;
    string      lastModified;

    std::vector<string > properties;
    disk.open(DISK_NAME);
    if (disk.is_open())
    {
        while (getline(disk, line))
        {
            properties = parseInput(line);
            if (properties.size() > 0)
            {
                fileType = properties[0][0];
                fileName = properties[1];
                filePath = properties[2];
                lastModified = properties[3] + " " + properties[4] + " " + properties[5];
                if (fileType == REGULAR_FILE)
                {
                    size_t size = std::stoi(properties[6]);
                    string content;
                    loadRegularFileContent(content, disk);
                    loadRegularFile(fileName, filePath, lastModified, content, size);
                }
                else if (fileType == DIRECTORY)
                {
                    loadDirectory(fileName, filePath, lastModified);
                }
            }
        }
    }
    else
        throw std::runtime_error(CAN_NOT_OPEN_DISK);
    disk.close();
}

//throws exception
void MyOs::loadDirectory(const string& name, const string& path, const string& lastModified)
{
    Directory *newDir = new Directory(name, path, lastModified);
    if (rootDir == nullptr)
    {
        newDir->addFile(new Directory(".", path, lastModified));
        newDir->setPrevDir(nullptr);
        rootDir = newDir;
    }
    else
    {
        string    parentDirPath = path.substr(0, path.find_last_of("/"));
        if (parentDirPath.empty())
            parentDirPath = "/";
        Directory *parentDir = dynamic_cast<Directory *>(getSpesificFile(parentDirPath));
        if (parentDir == nullptr)
            throw std::runtime_error(NO_SUCH_DIR);
        newDir->addFile(new Directory(".", path+"/.", lastModified));
        newDir->addFile(new Directory("..", path+"/..", parentDir->getLastModified()));
        newDir->setPrevDir(parentDir);
        parentDir->addFile(newDir);
    }
}

//throws runtime error
void MyOs::loadRegularFile(const string& name, const string& path, const string& lastModified, const string& content, const size_t& size)
{
    string     parentDirPath = path.substr(0, path.find_last_of("/"));
    if (parentDirPath.empty())
        parentDirPath = "/";
    RegularFile *newFile = new RegularFile(name, path, lastModified, content, size);
    Directory   *parentDir = dynamic_cast<Directory *>(getSpesificFile(parentDirPath));
    if (parentDir != nullptr)
        parentDir->addFile(newFile);
    else
        throw std::runtime_error(NO_SUCH_DIR);
}

void MyOs::loadRegularFileContent(std::string& content, std::ifstream &file)
{
    string  line;
    getline(file, line);
    while (getline(file, line) && line != "%")
    {
        content += line;
        content += "\n";
    }
    content.pop_back(); //remove last \n
}

//throws runtime error
void MyOs::writeDisk(File* data)
{
    ofstream disk;

    disk.open(DISK_NAME, std::ios::app);
    if (data == nullptr)
        throw std::runtime_error(NULLDATA);
    if (disk.is_open())
    {
        if (data->getType() == DIRECTORY)
        {
            Directory* dir = dynamic_cast<Directory *>(data);
            disk << *dir << "\n";
        }
        else if (data->getType() == REGULAR_FILE)
        {
            RegularFile* file = dynamic_cast<RegularFile *>(data);
            disk << *file << "\n";
            diskSize += file->getSize();
        }
    }
    else
        throw std::runtime_error(CAN_NOT_OPEN_DISK);
    disk.close();
}

Directory* MyOs::getCurrentDir()
{
    return curDir;
}

