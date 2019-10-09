/**My Remove Class- This removes the given files listed as parameters to this command.
    *
    *  Author: Ositadinma Arimah
    *  2019-10-03
    *
    */

#include "FileManager.h"
using namespace std;

int main(int argc, char *argv[]){
    if (argc < 1){
        std::cout << "Error: At least 1 argument is required" << std::endl;
        exit(EXIT_FAILURE);
    }else{
        for(int i = 1; i < argc; ++i){
            FileManager fileManager(argv[i]);
            fileManager.removeFile();
        }
    }
}
