/**MyMv Class- This is used to move and rename files around,
    *
    *  Author: Ositadinma Arimah
    *  2019-10-03
    *
    */



#include "FileManager.h"
using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Error: 3 arguments are required" << std::endl;
        exit(EXIT_FAILURE);
    }else{
        FileManager oldFile(argv[1]);
        oldFile.renameFile(argv[2]);
        if(oldFile.getErrorValue()!=0){
            ofstream outStream;
            outStream.open(argv[2]);
            oldFile.dumpFile(outStream);
            outStream.close();
            oldFile.removeFile();
        }
    }
}
