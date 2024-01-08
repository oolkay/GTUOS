//THIS FILE IS THE TEST CODE FOR THE REGULAR FILE CLASS
//YOU CAN COMPILE THIS FILE WITH THE FOLLOWING COMMAND:
//g++ -std=c++11 testCodeRegularFile.cpp ../src/File.cpp ../src/RegularFile.cpp 

#include "../inc/RegularFile.hpp"
#include <stdexcept>
#include <iostream>
#include <vector>

using std::string;
using std::vector;
using std::cout;
using std::endl;

const string CURRENT_DIR = "/home/omer";

void ls(const vector<File *>& files)
{
    for (const auto file : files)
    {
        if (file->getPath() == CURRENT_DIR)
        {
            file->ls();
        }
    }
}

int main()
{
    string inp;
    vector<File *> files;
    files.push_back(new RegularFile(".", "/home/omer", 0, "0.txtden selamlar"));
    files.push_back(new RegularFile("..", "/home/omer", 0, "0.txtden selamlar"));
    files.push_back(new RegularFile("1.txt", "/home/omer", 0, "1.txtden selamlar"));
    files.push_back(new RegularFile("2.txt", "/home/omer", 0, "2.txtden selamlar"));
    files.push_back(new RegularFile("3.txt", "/home/omer", 0, "3.txtden selamlar"));
    while (inp != "exit")
    {
        //readInput funct
        cout << "> ";
        getline(std::cin, inp);

        if (inp == "ls")
        {
            ls(files);
        }
    }
}