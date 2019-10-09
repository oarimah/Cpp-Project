/**My Stat Class- This outputs all of the information on the file named as a parameter to this command.
    *
    *  Author: Ositadinma Arimah
    *  2019-10-03
    *
    */
#include "FileManager.h"
using namespace std;
int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Error: Only 1 argument is required, now exiting ..." << std::endl;
        exit(EXIT_FAILURE);
    } else {
        FileManager file(argv[1]);


        std::cout << "This file's name is: " <<file.getName()<<".\n";
        if(S_ISREG(file.getType())){
            std::cout << "This file's type is:Regular File" << ".\n";
        }else{
            std::cout << "This file's type is: Directory" << ".\n";
            std::cout << "This directory's children is/are: " <<file.listDirNames()<<".\n";
        }
        std::cout << "This file's size is: " <<file.getFileSize()<<".\n";
        std::cout << "This file's group is: " <<file.getGroup()<<".\n";
        std::cout << "This file's owner is: " <<file.getOwner()<<".\n";
        std::cout << "This file's last time of access is: " <<ctime(&(file.getAccessTime().tv_sec))<<".\n";
        std::cout << "This file's last time of modification is: " <<ctime(&(file.getModificationTime().tv_sec)) <<".\n";
        std::cout << "This file's last time of status change is: " <<ctime(&(file.getStatusChange().tv_sec)) << ".\n";
        std::cout << "This file's block size is: " <<(file.getBlockSize())<<".\n";
        std::cout << "This file's block permissions are: " <<file.getPermissions()<<".\n";
        std::cout << "This file's error Value " <<file.getErrorValue()<<".\n";
    }
}