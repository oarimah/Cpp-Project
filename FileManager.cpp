/**FileManager Class- creates a FileManager object
    *
    *  Author: Ositadinma Arimah
    *  2019-10-03
    *
    */




#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>
#include <vector>
#include <string>
#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <dirent.h>
#include <fstream>
#include <algorithm>
#include <cerrno>
#include <cstring>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include "FileManager.h"
using namespace std;


    /**FileManager Constructor- creates an intialized FileManager object
     *
     *  @param algName FileManager(string _filename)
     *  @param arguments _filename
     *  @return an initialzed FileManager object
     *
     */
    FileManager::FileManager(string _filename) { //constructor for FileManager object, initiazlizes all variables
            this->_filename = _filename;
            struct stat buf;
            stat(_filename.c_str(),&buf);
            this->type = buf.st_mode;
            this->groupOwner = buf.st_gid;
            this->permissions = buf.st_mode;
            this->modTime = buf.st_mtim;
            this->accessTime = buf.st_atim;
            this->statusTime = buf.st_ctim;
            this->errorValue = 0;
            this->size = buf.st_size;
            std::vector<std::string> vec;
            this->owner = buf.st_uid;
            this->blockSize = buf.st_blksize;
            this->stringError;
        }

    /**FileManager Destructor- destroys the vector when called.
     *
     *  @param algName: ~FileManager()
     *  @param arguments: none
     *  @return: a freed vector
     *
     */
    FileManager :: ~FileManager() {
       for (unsigned int i = 2; i < vec.size(); i++) {//loop through the vector and delete each entry in the vector
           delete vec[i];
       }

   }

    /**FileManager renameFile()- renames the FileManager object to the passed parameter
     *
     *  @param algName: renameFile(char *new_filename)
     *  @param arguments: char *new_filename
     *  @return: a statement regarding whether the rename was passed or failed.
     *
     */
   void FileManager::renameFile(char *new_filename) {
           if (rename(_filename.c_str(), new_filename) != 0){//use the rename to switch oldfilename to new filename
               perror("Error renaming file");
               errorValue = errno;

           }else
               std::cout << "File renamed successfully";
           errorValue = 0;
       }

    /**FileManager removeFile()- renmoves the FileManager object this function is called on
     *
     *  @param algName: removeFile()
     *  @param arguments: none
     *  @return: a statement regarding whether the remove was passed or failed.
     *
     */
     void FileManager::removeFile() {//use the unlink function to remove a file
       if (unlink(_filename.c_str()) != 0) {
           perror("Error removing file");
           errorValue = errno;
       }else {
           std::cout << "File removed successfully";
           errorValue = 0;
       }

    }

   /**FileManager compareFiles()- compare FileManager object to the passed parameter
      *
      *  @param algName: compareFiles(FileManager &fileManager)
      *  @param arguments: FileManager &fileManager
      *  @return: true if files are the same and returns false if files are different, error message if files could not be compared
      *
      */
    bool FileManager::compareFiles(FileManager &fileManager) {
       ifstream inFile;
       inFile.open(_filename);
       if (inFile.is_open()) {//if the file is open create a new stream which opens the passed parameter
           ifstream outFile;
           outFile.open(fileManager.getName());//open the passed file
           if (outFile.is_open()) {
               char originalLine[size];//create buffer with size of original filemanager object
               char fileLine[fileManager.getFileSize()];
               inFile.read(originalLine, size);
               outFile.read(fileLine, size);
               if (strcmp(originalLine, fileLine) == 0)// use string compare from c library, if 0 return true
                   return true;
           } else
               return false;
           errorValue = 0;
       } else
           errorValue = errno;

       return false;

   }

    /**FileManager dumpFile()- dump contents of FileManager object to an ofstream
          *
          *  @param algName: dumpFile(std::ofstream &fileStream)
          *  @param arguments: std::ofstream &fileStream- the stream for the contents to be dumped in
          *  @return:  if successful contents of file will be copied into the stream, else store errorValue as error
          *
          */
   void FileManager::dumpFile(std::ofstream &fileStream) {
       if (!S_ISREG(type)) {
           std::cout << "Error: This is not a file" << ".\n";
           errorValue = ENOTSUP;
       } else {
           if (fileStream.is_open()) {
               ifstream inFile;
               inFile.open(_filename);
               if(inFile.is_open()) {
                   char line[size];
                   inFile.read(line, size);
                   inFile.close();
                   fileStream.write(line, size);
                   errorValue = 0;
               }
           } else {
               errorValue = errno;
           }

       }
   }


    /**FileManager expandFiles()- This function operates on directories only and is used to fill in the children of the file object this function was invoked upon
           *
           *  @param algName: expandDirectory()
           *  @param arguments: none
           *  @return:  error code if the operation could not be completed, and it should store the error number generated in the process in the appropriate attribute
           *
           */
   void FileManager:: expandDirectory(){
   DIR *dir;//pointer to directory
   struct dirent *entry; // all stuff in the directory
   dir = opendir(_filename.c_str());
   entry = readdir(dir);
   if (!dir){
       cout << "Directory not found" << endl;
       errorValue = errno;
       return;
   }else if((S_ISREG(type))){//check if regular file
       cout << "Error, this input is a file" << endl;
       errorValue = ENOTSUP;
   }else if ((S_ISDIR(type))){//check if directory
       while(entry!= nullptr) {
           vec.push_back(new FileManager(_filename+"/"+entry->d_name));//push a new file object into the vector
           errorValue = 0;
       }
   }
}

    /**FileManager listDirNames()- list the children of said directory as a string
            *
            *  @param algName: listDirNames()
            *  @param arguments: none
            *  @return:  string of all children in a directory
            *
            */
    std::string FileManager:: listDirNames(){
       expandDirectory();
       string namesOfChildren;
       for(int i=0;i<vec.size();i++){
           namesOfChildren.append(vec[i]->getName()+"\n");
       }
       return namesOfChildren;
   }

    /**FileManager getName() get the name of filemanager object
              *
              *  @param algName: getName()
              *  @param arguments: none
              *  @return:  _filename
              *
              */
    std::string FileManager::getName() {
        return _filename;
    }


    /**FileManager getName() get the type of filemanager object
          *
          *  @param algName: getType()
          *  @param arguments: none
          *  @return:  type
          *
          */
    mode_t FileManager::getType() {
        return type;
    }

    /**FileManager getFileSize() get the file size of filemanager object
              *
              *  @param algName: getFileSize()
              *  @param arguments: none
              *  @return:  size
              *
              */
    off_t FileManager::getFileSize() {
        return size;
    }


    /**FileManager getOwner() get the owner of filemanager object as string
          *
          *  @param algName: getOwner()
          *  @param arguments: none
          *  @return:  owner as a string
          *
          */
    std::string FileManager::getOwner() {//return the owner of the file as a string
        struct passwd *pwd;
        pwd = getpwuid(owner);
        return pwd->pw_name;
    }
    /**FileManager getGroup() get the owner of filemanager object as string
      *
      *  @param algName: getGroup()
      *  @param arguments: none
      *  @return:  group as a string
      *
      */
    std::string FileManager::getGroup() {// return the group owner as a string
        struct group *grp;
        grp = getgrgid(groupOwner);
        return grp->gr_name;
    }

    /**FileManager getPermissions() get the permissions of an object as atring
      *
      *  @param algName: getPermissions()
      *  @param arguments: none
      *  @return:  permissions as a string
      *
      */
    char* FileManager::getPermissions(){ //print out the permissions in the correct order
        char *modeValue = (char*)malloc(sizeof(char) * 9 + 1);

            modeValue[0] = (permissions & S_IRUSR) ? 'r' : '-';
            modeValue[1] = (permissions & S_IWUSR) ? 'w' : '-';
            modeValue[2] = (permissions & S_IXUSR) ? 'x' : '-';
            modeValue[3] = (permissions & S_IRGRP) ? 'r' : '-';
            modeValue[4] = (permissions & S_IWGRP) ? 'w' : '-';
            modeValue[5] = (permissions & S_IXGRP) ? 'x' : '-';
            modeValue[6] = (permissions & S_IROTH) ? 'r' : '-';
            modeValue[7] = (permissions & S_IWOTH) ? 'w' : '-';
            modeValue[8] = (permissions & S_IXOTH) ? 'x' : '-';
            modeValue[9] = '\0';
            return modeValue;
        }



    /**FileManager getAccessTime() get the access time
          *
          *  @param algName: getAccessTime()
          *  @param arguments: none
          *  @return:  the access time
          *
          */
    const timespec& FileManager::getAccessTime() {
        return accessTime;
    }


    /**FileManager getModificationTime() get the modification time
          *
          *  @param algName: getModificationTime()
          *  @param arguments: none
          *  @return:  the modification time
          *
          */
    const timespec& FileManager::getModificationTime() {
        return modTime;
    }

    /**FileManager getStatusTime() get the status time
          *
          *  @param algName: getStatusTime()
          *  @param arguments: none
          *  @return:  the status time
          *
          */
    const timespec& FileManager::getStatusChange() {
        return statusTime;
    }

    /**FileManager getBlockSize() get the block size of a file
              *
              *  @param algName: getBlockSize()
              *  @param arguments: none
              *  @return:  the block size
              *
              */
    blksize_t FileManager::getBlockSize() {
        return blockSize;
    }


    /**FileManager listdir() return all the children to a vector
      *
      *  @param algName: listdir()
      *  @param arguments: none
      *  @return:  the vector which stores the children
      *
      */
    vector<FileManager*>& FileManager::listdir()  {//use a vector to return all the children in a said directory
        return vec;
    }

    /**FileManager getErrorValue() return the error value of file manager object
   *
   *  @param algName: getErrorValue()
   *  @param arguments: none
   *  @return:  the errorValue which was stored by using errno
   *
   */
    int FileManager::getErrorValue() {
        errorValue = errno;
        return errorValue;
    }

    /**FileManager getStringErrorValue() return all the children to a vector
      *
      *  @param algName: getStringErrorValue()
      *  @param arguments: none
      *  @return:  return error Value as a string
      *
      */
    std::string FileManager::getStringErrorValue() {// set the error Value as a string
        stringError = strerror(errno);
        return stringError;

    }





