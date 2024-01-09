#include "../inc/MyOs.hpp"
#include <stdexcept>
#include <iostream>
#include <vector>

using std::string;
using std::vector;
using std::cout;
using std::endl;
using namespace OlkayOS;

int main()
{
    cout << "\nAVAILABLE COMMANDS: " << endl;
    cout << "ls,  ls -R" << endl;
    cout << "cd" << endl;
    cout << "mkdir" << endl;
    cout << "rm,  rm -r (for directories)" << endl;
    cout << "cp" << endl;
    cout << "cat" << endl;
    cout << "link" << endl;
    cout << "pwd" << endl;
    cout << "exit\n" << endl;



    MyOs::init();
    MyOs::run();
}