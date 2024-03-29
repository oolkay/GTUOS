#ifndef DEFINES_HPP
#define DEFINES_HPP

#define DIR_SIZE      4096
#define LINK_SIZE     6
#define DISK_SIZE     10*1024*1024


#define GREETING      "WELCOME TO THE olkayOS"

#define UNKNOWN_CMD  "[ERROR] Command not found"
#define MISSING_ARG  "[ERROR] Missing argument"
#define EXTRA_ARG    "[ERROR] Too many arguments"
#define CAN_NOT_REMOVE "[ERROR] You can not remove"
#define CAN_NOT_LINK "[ERROR] The linked file is already exist"
#define USER_NAME    "omer"
#define HOST_NAME    "olkayOS"
#define REGULAR_FILE 'F'
#define LINK         'L'
#define DIRECTORY    'D'
#define NO_SUCH_DIR  "[ERROR] No such directory"
#define DIR_EXIST    "[ERROR] Directory already exists"
#define IS_DIR       "[ERROR] It is a directory"
#define IS_NOT_DIR   "[ERROR] It is not a directory"
#define NO_SUCH_FILE "[ERROR] No such file"
#define SAME_FILE    "[ERROR] The file is already exist"
#define SAME_DIR     "[ERROR] You can not copy directory to itself"
#define NO_LINK "[ERROR] The file that being linked is not exist"
#define ONLY_CUR "[ERROR] You can only copy to current directory"
#define NO_DIR_FILE "[ERROR] No such directory or file"
#define INVALID_DEST "[ERROR] Invalid dest name"
#define RM_CUR_DIR "[ERROR] You can not remove current directory"
#define DISK_FULL "[ERROR] Operation cancelled, there is no enough space in disk"
#define DISK_NAME "disk.txt"
#define INVALID_DIR_NAME "[ERROR] Invalid directory name"
#define CAN_NOT_OPEN_DISK "[ERROR] Can not open disk"
#define NULLDATA "[ERROR] Null data"


#define DEFAULT "\033[0;39m"
#define GRAY "\033[0;90m"
#define RED "\033[0;91m"
#define GREEN "\033[0;92m"
#define YELLOW "\033[0;93m"
#define BLUE "\033[0;94m"
#define MAGENTA "\033[0;95m"
#define CYAN "\033[0;96m"
#define WHITE "\033[0;97m"
#define BG_CYAN "\033[0;46m"
#define BG_MAGENTA "\u001b[45m"

#endif