/**MyCat Class-  Like the original command, this will display the
 * contents of all of the files given as parameters to the command to the terminal.
*
*  Author: Ositadinma Arimah
*  2019-10-03
*
*/



#include "FileManager.h"
using namespace std;

int main(int argc, char *argv[]){
  if (argc <= 1){
    std::cout << "Error: At least 1 argument is required" << std::endl;
    exit(EXIT_FAILURE);
  }else {
      for(int i = 1; i < argc; ++i){
          FileManager fileManager(argv[1]);
          ofstream wFile;
          string catText = "catText.txt";
          wFile.open(catText);
          fileManager.dumpFile(wFile);
          wFile.close();
          FileManager catManager(catText);
          ifstream ifstream;
          char line[catManager.getBlockSize()];
          ifstream.open(catText);
          ifstream.read(line,catManager.getBlockSize());
          cout<< line;
          ifstream.close();
          catManager.removeFile();
      }

  }
}