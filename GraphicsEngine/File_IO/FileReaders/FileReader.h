#ifndef _FILE_READER_H_
#define _FILE_READER_H_
#include <fstream>
#include "../../Utils/String/StringUtils.h"
typedef unsigned int uint;

enum FileType
{
    TYPE_ERROR = 0,
    TGA_24, //Does not have an alpha channel
    TGA_32,
};

struct FileInfo
{
    FileType type;
    unsigned char* data = nullptr;
    bool success = false;
};

template<class T>
struct FileReader
{
    static bool CheckExtention(char* extention);
    static FileInfo* ReadFile(char* filePath); // this needs to be a path reletive to the drive
};

#endif //!_FILE_READER_H_