//THIS FILE IS THE TEST CODE FOR THE REGULAR FILE CLASS
//YOU CAN COMPILE THIS FILE WITH THE FOLLOWING COMMAND:
//g++ -std=c++11 testCodeRegularFile.cpp ../src/File.cpp ../src/RegularFile.cpp 

#include "../inc/RegularFile.hpp"
#include <stdexcept>
#include <iostream>
#include <vector>
#include "../inc/Directory.hpp"

using std::string;
using std::vector;
using std::cout;

const string CURRENT_DIR = "/home/omer";

int main()
{
    string inp;
    vector<File *> files;
    files.push_back(new Directory(".", "/home/omer", 0));
    files.push_back(new Directory("..", "/home/omer", 0));
    while (inp != "exit")
    {
        //readInput funct

        if (inp == "ls")
        {
            for (const auto file : files)
            {
                if (file->getPath() == CURRENT_DIR)
                {
                    file->ls();
                }
            }
        }
        else if (inp == "mkdir")
        {
            files.push_back(new Directory("newDir", "/home/omer", 0));
        }

    }
    return (0);
}