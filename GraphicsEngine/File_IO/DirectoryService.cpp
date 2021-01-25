#include "DirectoryService.h"
#include <Windows.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <iostream>
#include <fstream>  

#include <sstream>

#include "../Utils/String/StringUtils.h"
#include "../File_IO/JsonUtils.h"

using namespace JsonUtils;

#define DBOUT( s )            \
{                             \
   std::wostringstream os_;   \
   os_<< '\n';				\
   os_ << s;                   \
   OutputDebugStringW( os_.str().c_str()  );  \
}

void DirectoryService::Initialise()
{
	Json file;
	file.ReadFromFile("ProjectSettings/Config.json");
	JsonElement* element = file.Find("Paths");
    if(element != nullptr)
    {
        ArrayElement* array = static_cast<ArrayElement*>(element);
		m_directoryTagCount = array->elements.size();
        m_directoryTags = new char*[m_directoryTagCount];
        m_directoryPaths = new char*[m_directoryTagCount];
        for(int i = 0; i < m_directoryTagCount; ++i)
        {
			int tagLength = StrUtils::GetLength(array->elements[i]->tag)+1;
            m_directoryTags[i] = new char[tagLength];
			for (int j = 0; j < tagLength; ++j)
			{
				m_directoryTags[i][j] = array->elements[i]->tag[j];
			}
			char* element = static_cast<ValueElement*>(array->elements[i])->element;
			tagLength = StrUtils::GetLength(element)+1;
			m_directoryPaths[i] = new char[tagLength];
			for (int j = 0; j < tagLength; ++j)
			{
				m_directoryPaths[i][j] = element[j];
			}
			
        }
    }
}
//program directory (we know this path exists)

char* DirectoryService::GetTagPath(char* directoryTag)
{
	for(int i = 0; i < m_directoryTagCount; ++i)
	{
		if(StrUtils::Compare(directoryTag, m_directoryTags[i]))
		{
			return m_directoryPaths[i];
		}
	}
	return nullptr;
}

char* DirectoryService::ReplaceDirectoryTags(char* filePath)
{
	int firstTag = StrUtils::Find(filePath, '$');
	if(firstTag != -1)
	{	
		++firstTag; // $ -> c
		int secondTag = StrUtils::Find(filePath, '$', firstTag);

		if(secondTag != -1)
		{
			char* tag = StrUtils::copy(filePath, firstTag, (secondTag) - firstTag);
			char* path = GetTagPath(tag);
			int filePathLength = StrUtils::GetLength(filePath);
			++secondTag;
			char* filePathNoTag = StrUtils::copy(filePath, secondTag, filePathLength - secondTag);
			return ReplaceDirectoryTags(StrUtils::Append(path, filePathNoTag)); //Keep replacubg tags untill non remain.
		}
	}
	return filePath; //noTags
}


bool DirectoryService::DoesFilePathExist(char* filePath)
{
	char *cpy_dirToCheck = filePath;

	int pos = 0;
	WCHAR *pwFilePath = new WCHAR[255];

	cpy_dirToCheck = filePath;
	while ((*cpy_dirToCheck) != '\0')
	{
		if (pos >= 243)
		{
			DBOUT("!! NEED TO CHANGE TO THE UNICODE CREATE DIR AS THE DESIRED PATH EXCEEDS 248 characters !!");
			delete pwFilePath;
			return false;
		}

		pwFilePath[pos] = *cpy_dirToCheck;

		if (*cpy_dirToCheck == '\\' || *cpy_dirToCheck == '/')
		{
			pwFilePath[pos + 1] = '\0';

			DWORD bitmask = GetFileAttributes(pwFilePath);
			DBOUT("DIR: " << pwFilePath << " Bit Mask : " << bitmask);
			if (bitmask != INVALID_FILE_ATTRIBUTES && (0 != (bitmask & FILE_ATTRIBUTE_DIRECTORY)))
			{
				DBOUT("Path exists!");
			}
			else
			{
				return false;
			}

		}
		++cpy_dirToCheck;
		
		++pos;
	}
	delete pwFilePath;
	return true;
}



//we dont know that the directory filepath exists
bool DirectoryService::CreateFileInDirectory(char* filePath)
{
    // CreateDirectory(char* filePath, LPSECURITY_ATTRIBUTES)
    char *filePathModified = nullptr, *file = nullptr, *cpy_filepath = filePath;
    int length = 0, fileNameLength = 0;
    char *cpy_filePathModified;  


	//CreateDirectory can only create one new path at a time! need to split the path up and append each section
    if (CreateFolders(filePath))
    {
        std::ofstream outfile (filePath);
        outfile.close();
        return true;
    }

    return false;
}

//0 returned if the operation succeeds, -1 if fails
// https://pubs.opengroup.org/onlinepubs/009695399/functions/stat.html
bool DirectoryService::DoesFileExsist(char* filePath, bool checkDir)
{
    struct stat buffer;
	bool val = (stat(filePath, &buffer) == 0);
	if (checkDir)
	{
		val &= DoesFilePathExist(filePath);
	}
    return val;
}


void DirectoryService::CreatePath(char* filePath)
{
    CreateFolders(filePath);
}
//
bool DirectoryService::CreateFolders(char* directoryToCreateFromDir)
{
	//how many directories are there to be made/created

	char *cpy_directoriesToCreate = directoryToCreateFromDir;

	int pos = 0;
	WCHAR *pwFilePath = new WCHAR[243];

    cpy_directoriesToCreate = directoryToCreateFromDir;
	while ((*cpy_directoriesToCreate) != '\0')
	{
        if (pos >= 248)
        {
            DBOUT("!! NEED TO CHANGE TO THE UNICODE CREATE DIR AS THE DESIRED PATH EXCEEDS 248 characters !!");
            delete pwFilePath;
            return false;
        }

        pwFilePath[pos] = *cpy_directoriesToCreate;

        if (*cpy_directoriesToCreate == '\\' || *cpy_directoriesToCreate == '/')
        {
            pwFilePath[pos + 1] = '\0';

            DWORD bitmask = GetFileAttributes(pwFilePath);
            DBOUT("DIR: " << pwFilePath << " Bit Mask : " << bitmask);
            if (bitmask != INVALID_FILE_ATTRIBUTES && (0 != (bitmask & FILE_ATTRIBUTE_DIRECTORY)))
            {
                DBOUT("Path exists!");
            }
            else
            {
                if (CreateDirectoryW(pwFilePath, NULL) == TRUE)
                {
                    DBOUT("created path : " << pwFilePath);
                }
                else
                {
                    DBOUT("Failed to create path : " << pwFilePath);
                }
            }

        }
        ++cpy_directoriesToCreate;
		++pos;
	}
	delete pwFilePath;
	return true;
}