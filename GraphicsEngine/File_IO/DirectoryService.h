#ifndef _DIRECTORY_SERVICE_H_
#define _DIRECTORY_SERVICE_H_

#include "../Utils/Singleton.h"

class DirectoryService : public Singleton<DirectoryService>
{
    private:
    char** m_directoryTags; //$ProjectDir$
    char** m_directoryPaths; //C:\\blah
    unsigned short m_directoryTagCount;

		bool CreateFolders(char* directoryToCreateFromDir);

    public:
		void Initialise();
        void CreatePath(char* filePath);
    bool DoesFilePathExist(char* filePath);
    bool DoesFileExsist(char* filePath, bool checkDir = false);
    char* ReplaceDirectoryTags(char* filePath);
    bool CreateFileInDirectory(char* filePath);
    char* GetTagPath(char* directoryTag);
};

#endif //!_DIRECTORY_SERVICE_H_