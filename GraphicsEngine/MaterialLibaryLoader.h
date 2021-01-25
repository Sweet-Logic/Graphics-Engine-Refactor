#pragma once

#include <string>
#include <Vector>

#include "Texture2D.h"

enum Map
{
	rAmbient = 0,
	rDiffuse = 1,
	rSpecular = 2,
	eSpecular = 3,
	Disolved = 4,
	Bump = 5,
};

struct MaterialOld
{
	std::string MaterialName;
	float Ns; //Specular Exponent
	float Ni;
	float d; //disolved -- The transparancy 1.0 = opaque. but not depenent on the thickness of the material
	float Tr; //disolved (inverted: Tr = 1 - d) if d = 0.3, Tr = 0.7
	float Tf[3];
	int illum; //Illumination Model
	float Ka[3]; //Diffuse Colour
	float Kd[3]; //Ambient Colour
	float Ks[3]; //Specular Colour
	float Ke[3]; 
	Texture2D* LoadedTextures[6]{nullptr, nullptr,nullptr,nullptr,nullptr,nullptr};
	std::string* FilePaths;
};

struct Libary
{
	std::string LibaryName = "";
	int MaterialCount = 0;
	MaterialOld** LoadedMaterials;
};



class MaterialLibaryLoader
{
public:

	~MaterialLibaryLoader();
	static MaterialLibaryLoader* GetInstance()
	{
		if (_instance)
		{
			_instance = new MaterialLibaryLoader;
		}
		return _instance;
	}

	static MaterialLibaryLoader* GetInstance(ID3D11Device *&Device, ID3D11DeviceContext *&DeviceContext)
	{
		_device = Device;
		_deviceContext = DeviceContext;
		return GetInstance();
	}

	Libary* GetLibary(std::string libaryName) const 
	{
		for (std::vector<Libary*>::size_type i = 0; i < LoadedLibaries.size(); i++)
		{
			if (LoadedLibaries.at(i)->LibaryName == libaryName)
			{
				return LoadedLibaries.at(i);
			}
		}
		return nullptr;
	}

	MaterialOld* GetMaterial(std::string materialName, Libary *&libaryToSearch) const
	{
		for (int i = 0; i < libaryToSearch->MaterialCount; i++)
		{
			if (libaryToSearch->LoadedMaterials[i]->MaterialName == materialName)
			{
				return libaryToSearch->LoadedMaterials[i];
			}
		}
		return nullptr;
	}


	static Libary* LoadMtl(std::string filepath);


private:
	MaterialLibaryLoader();

	static std::vector<Libary*> LoadedLibaries;
	static MaterialLibaryLoader* _instance;

	static ID3D11Device* _device;
	static ID3D11DeviceContext* _deviceContext;

};

