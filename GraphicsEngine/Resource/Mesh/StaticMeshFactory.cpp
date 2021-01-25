#include "StaticMeshFactory.h"
#include "../../File_IO/FileReaders/Mesh/ObjReader.h"

StaticMesh* STATIC_MESH_FACTORY::Create(char* filePath)
{
    StaticMesh* staticMesh = nullptr;
    

    //Evaluate the file extention
    unsigned int pathLength = StrUtils::GetLength(filePath);
    int extStart = StrUtils::rFind(filePath, '.');

    char* ext = StrUtils::copy(filePath, extStart, pathLength - extStart);
	
    //obj
	if (OBJ_READER::CheckExtention(ext))
	{
		OBJ_Info* fileInfo = static_cast<OBJ_Info*>(OBJ_READER::ReadFile(filePath));

		staticMesh->m_elements = fileInfo->meshs;
		staticMesh->m_elementCount = fileInfo->meshCount;
	}
    //fbx
    //3ds
    //stl?


    return staticMesh;
}

StaticMesh* STATIC_MESH_FACTORY::Create(Resource* resource)
{
    StaticMesh* staticMesh = static_cast<StaticMesh*>(resource);
    
    //Evaluate the file extention
    char* path = resource->GetFilePath();
    unsigned int pathLength = StrUtils::GetLength(path);
    int extStart = StrUtils::rFind(path, '.');

    char* ext = StrUtils::copy(path, extStart, pathLength - extStart);
	
    //obj
	if (OBJ_READER::CheckExtention(ext))
	{
		OBJ_Info* fileInfo = static_cast<OBJ_Info*>(OBJ_READER::ReadFile(path));

		staticMesh->m_elements = fileInfo->meshs;
		staticMesh->m_elementCount = fileInfo->meshCount;
	}
    //fbx
    //3ds
    //stl?
    
    return staticMesh;
}
