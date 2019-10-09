/**MyLs Class- For a directory, this will list the contents of the directory and for other types of files,
 * it will show the file's name, just as ls would.
    *
    *  Author: Ositadinma Arimah
    *  2019-10-03
    *
    */

//Could not finish other cases of this function


#include "FileManager.h"
using namespace std;

int main(int argc, char* argv[]) {
    if (argc > 3) {
        std::cout << "Error: Too many arguments entered" << std::endl;
        exit(EXIT_FAILURE);
    } else if (argc == 1) {
        FileManager file1(".");
        file1.expandDirectory();
        for (int i = 2; i < file1.listdir().size(); i++)
            std::cout << file1.listdir()[i]->getName() << std::endl;
    }
}
//    } else if (argc == 2) {
//        if (stat(argv[1], &s) == 0 ){
//            if (s.st_mode & S_IFREG) {
//                FileManager file(argv[1]);
//                std::cout << "This is a file and its filename is: " << file.getName() << ".\n";
//            } else if (s.st_mode & S_IFREG) {
//                FileManager file2(argv[1]);
//                file2.listdir(argv[1]);
//                std::cout << "This is a directory and its directory contents are: " << file2.listdir(argv[1]) << ".\n";
//            } else {
//                std::cout << "Error: File or Directory does not exist" << ".\n";
//                exit(EXIT_FAILURE);
//            }
//        }else{
//            std::cout << "Error: opening a file or directory with the name provided" << std::endl;
//            exit(EXIT_FAILURE);
//        }
//    } else if (argc == 3) {
//        if ((std::strcmp(argv[2], "-l") == 0)) {
//            struct dirent *entry;
//            DIR *dir = opendir(argv[1]);
//            if (dir == nullptr) {
//                std::cout << "Error: Directory is not opening" << std::endl;
//                exit(EXIT_FAILURE);
//            }
//            while ((entry = readdir(dir)) != nullptr) {
//                cout << entry->d_name << endl;
//            }
//            closedir(dir);
//        }
//
//
//    }
//
//
