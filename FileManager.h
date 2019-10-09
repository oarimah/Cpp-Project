#ifndef  FILEMANAGER_H_
#define  FILEMANAGER_H_

    #include <pwd.h>
    #include <grp.h>
    #include <sys/stat.h>
    #include <vector>
    #include <string>
    #include <iostream>
    #include <cstdio>
    #include <unistd.h>
    #include <dirent.h>
    #include <algorithm>
    #include <cerrno>
    #include <stdlib.h>
    #include <time.h>
    #include <chrono>
    #include <fstream>
    #include <cstring>
    #include <iomanip>


    class FileManager {

public:
    FileManager(std::string filename);
    ~FileManager();
    void renameFile(char *new_filename);
    void removeFile();
    bool compareFiles(FileManager &fileManager);
    void dumpFile(std::ofstream &fileStream);
    void expandDirectory();
    std::string listDirNames();
    std::string getName();
    mode_t getType();
    off_t getFileSize();
    std::string getOwner();
    std::string getGroup();
    char* getPermissions();
    const timespec& getAccessTime();
    const timespec& getModificationTime();
    const timespec& getStatusChange();
    blksize_t getBlockSize();
    std::vector<FileManager*>& listdir();
    int getErrorValue();
    std::string getStringErrorValue();

private:
    std::string _filename;
    mode_t type;
    off_t size;
    gid_t groupOwner;
    mode_t permissions;
    timespec accessTime;
    timespec modTime;
    timespec statusTime;
    blksize_t blockSize;
    std::vector<FileManager*> vec;
    int errorValue;
    uid_t owner;
    std::string stringError;
};
#endif //FILEMANAGER_H_