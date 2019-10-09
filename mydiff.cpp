/**MyDiff Class- This compares two files named as parameters to this
 * command with one another and reports if they are the same or different.
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
    } else {
        FileManager file_1(argv[1]);
        FileManager file_2(argv[2]);
        if (!S_ISREG(file_1.getType()) || (!S_ISREG(file_2.getType()))) {
            std::cout << "Error: Arguments must be files ..." << std::endl;
        } else if (S_ISREG(file_1.getType()) && (S_ISREG(file_2.getType()))) {
            if (file_1.compareFiles(file_2)) {
                std::cout << "These files are the same" << std::endl;
            } else {
                std::cout << "These files are not the same" << std::endl;
            }
        }
    }
}