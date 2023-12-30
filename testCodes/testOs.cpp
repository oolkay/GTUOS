//THIS FILE IS THE TEST CODE FOR THE REGULAR FILE CLASS
//YOU CAN COMPILE THIS FILE WITH THE FOLLOWING COMMAND:
//g++ -std=c++11 testCodeRegularFile.cpp ../src/File.cpp ../src/RegularFile.cpp 

#include "../inc/MyOs.hpp"
#include <stdexcept>
#include <iostream>
#include <vector>

using std::string;
using std::vector;
using std::cout;
using std::endl;

int main()
{
    MyOs os;
    os.run();
}