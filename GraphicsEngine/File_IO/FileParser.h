#ifndef _FILEPARSER_H_
#define _FILEPARSER_H_

#include "../Utils/Singleton.h"

typedef unsigned long ulong;


class FileContents
{
    class FileComponent
    {

    };

    //std::pair<int, 
};

struct FileIO : public Singleton<FileIO>
{
    static FileContents ParseFile(char* filepath);
    static void WriteToFile(char* filepath, char** data);

    static ulong GetResourceIDFromMeta(char* filepath);
};

#endif //!_FILEPARSER_H_