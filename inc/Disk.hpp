#ifndef DISK_HPP
#define DISK_HPP

#include "Directory.hpp"
#include "RegularFile.hpp"

#define DISK_SIZE 1000000
#define DISK_NAME "disk.txt"
#define CAN_NOT_OPEN_DISK "[ERROR] Disk could not be opened"
#define NULLDATA "[ERROR] Data is null"

#include <string>
#include <vector>

using std::string;


class Disk
{
    public:
        Disk();

    private:
        Disk(const Disk& rhs);
        static std::size_t size;





};





#endif