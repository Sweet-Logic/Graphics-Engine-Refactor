#ifndef _FILE_HANDLER_H_
#define _FILE_HANDLER_H_
#include "../../Utils/Singleton.h"
#include <iostream>
#include <fstream> 

template<class T>
struct FileHandler : public Singleton<T> 
{
    virtual bool WriteToFile(char* filePath) = 0;
    virtual void ReadFromFile(char* filePath) = 0;
};

#endif //!_FILE_HANDLER_H_