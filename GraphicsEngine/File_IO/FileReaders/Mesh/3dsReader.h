#ifndef _3DS_READER_H_
#define _A3DS_READER_H_
#include "../FileReader.h"
#include <dxgiformat.h>

//Autodesk 3ds
struct A3DS_Info : FileInfo
{
};

class A3DS_READER : public FileReader<A3DS_READER>
{
};

bool FileReader<A3DS_READER>::CheckExtention(char* extention)
{
    return StrUtils::Compare(extention, ".3ds");
}

FileInfo* FileReader<A3DS_READER>::ReadFile(char* filePath)
{
    A3DS_Info* fileInfo = new A3DS_Info();
    
    return fileInfo;
}

#endif //!_TGA_READER_H_