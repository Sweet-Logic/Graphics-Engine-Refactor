#ifndef _RESOURCE_H_
#define _RESOURCE_H_
#include <exception>
#include "ResourceTypes.h"
#include "../File_IO/FileReaders/FileReader.h"

typedef unsigned long ulong;

class Resource
{
		friend class ResourceManager;
    
		ResourceType m_resourceType = ResourceType::E_RESOURCE;    
		char* m_name = nullptr;
		ulong m_id = ULONG_MAX;
		char* m_filePath = nullptr;
		bool m_isLoaded = false;
		FileInfo* m_fileInfo = nullptr;
    protected:
		void SetFileInfo(FileInfo* info)    {m_fileInfo = info;}
		void SetType(ResourceType type)     {m_resourceType = type;}
		void SetName(char* name)            {m_name = name;}
		void SetID(ulong id)                {m_id = id;}
		void SetFilePath(char* filePath) { 
			if (StrUtils::Compare(filePath, m_filePath))
			{ return; }
			delete[] m_filePath;
			m_filePath = filePath; 
		}
		void SetIsLoaded(bool loaded)       {m_isLoaded = loaded;}
    public:
		Resource() : m_resourceType(E_RESOURCE), m_name(nullptr), m_filePath(nullptr) {}
		Resource(ResourceType type) : m_resourceType(type), m_name(nullptr), m_filePath(nullptr) {}
    
		~Resource() {};

		FileInfo* const GetFileInfo()       {return m_fileInfo;}
		ResourceType const GetType()        {return m_resourceType;}
		char* const GetName()               {return m_name;}
		ulong const GetID()                 {return m_id;}
		char* const GetFilePath()           {return m_filePath;}
		bool const IsLoaded()               {return m_isLoaded;}

};

#endif //!_RESOURCE_H_