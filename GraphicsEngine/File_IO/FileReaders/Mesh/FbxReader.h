#ifndef _FBX_READER_H_
#define _FBX_READER_H_
#include "../FileReader.h"
#include <dxgiformat.h>

struct FBX_Info : FileInfo
{
};

class FBX_READER : public FileReader<FBX_READER>
{
};

bool FileReader<FBX_READER>::CheckExtention(char* extention)
{
    return StrUtils::Compare(extention, ".fbx");
}

FileInfo* FileReader<FBX_READER>::ReadFile(char* filePath)
{
    FBX_Info* fileInfo = new FBX_Info();
    
    return fileInfo;
}

#endif //!_TGA_READER_H_