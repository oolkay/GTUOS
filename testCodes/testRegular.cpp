//THIS FILE IS THE TEST CODE FOR THE REGULAR FILE CLASS
//YOU CAN COMPILE THIS FILE WITH THE FOLLOWING COMMAND:
//g++ -std=c++11 testCodeRegularFile.cpp ../src/File.cpp ../src/RegularFile.cpp 

#include "../inc/RegularFile.hpp"
#include <stdexcept>
#include <iostream>

int main()
{
    try
    {
        RegularFile file("ASD", "/home/ali", 0, "content");
        std::cout << file << std::endl;
        
    }
    catch (std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}