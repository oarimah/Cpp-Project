/**MyCpp Class- This is used to move and rename files around
    *
    *  Author: Ositadinma Arimah
    *  2019-10-03
    *
    */
#include "FileManager.h"
using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Error: 2 arguments required, now exiting ..." << std::endl;
        exit(EXIT_FAILURE);
    }else{
        FileManager oldFile(argv[1]);
        FileManager newFile(argv[2]);
        if(!S_ISREG(oldFile.getType())||(!S_ISREG(newFile.getType()))){
            std::cout << "Error: Arguments must be files ..." << std::endl;
        }else if(S_ISREG(oldFile.getType())&&(S_ISREG(newFile.getType()))){
            std::ofstream holdStream;
            holdStream.open(argv[2]);
            oldFile.dumpFile(holdStream);
            holdStream.close();
        }

    }
}
