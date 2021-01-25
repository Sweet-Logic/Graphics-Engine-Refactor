#pragma once
#include "MeshComponent.h"
#include "VertexTypes.h"
#include <vector>

struct FileInput
{
	std::string _objectName;

	Vertex* Verticies = nullptr;
	WORD** Indicies = nullptr;
	int* GroupIndicies;
	int TotalSmoothingGroups = 0;

	std::string MaterialLibary = "";
};

struct Processed
{
	int vert = 0;
	int normal = 0;
	int Tex = 0;
	int Position;

	Processed(int _vert, int _norm, int _tex, int pos)
	{
		vert = _vert;
		normal = _norm;
		Tex = _tex;
		Position = pos;
	}
};

struct Object
{
	std::string objName;
	MeshComponent* ObjectRef;

	Object(std::string name, MeshComponent* mesh)
	{
		objName = name;
		ObjectRef = mesh;
	}
};

class ObjLoader
{
public:
	~ObjLoader()
	{	
		_device->Release();
		for (std::vector<Object*>::size_type i = 0; i < LoadedObjects.size(); i++)
		{
			delete LoadedObjects.at(i)->ObjectRef;
			delete LoadedObjects.at(i);
		}
		LoadedObjects.clear();
		delete _instance;
	}

	static ObjLoader* GetInstance()
	{
		if (_instance)
		{
			_instance = new ObjLoader;
		}
		return _instance;
	}

	static ObjLoader* GetInstance(ID3D11Device* device)
	{
		_device = device;
		if (_instance)
		{
			_instance = new ObjLoader;
		}
		return _instance;
	}

	MeshComponent* LoadMeshFromFile(std::string filepath);

	MeshComponent* CreateMesh(std::string meshName, Vertex VertexData[], WORD indexData[], int vertexCount, int indexCount);
	
	//ObjFile Struct
	//Object Name
	
private:
	ObjLoader();

	static ID3D11Device* _device;
	static std::vector<Object*> LoadedObjects;
	static ObjLoader* _instance;
};

