#include "MaterialLibaryLoader.h"
#include <vector>

std::vector<Libary*> MaterialLibaryLoader::LoadedLibaries;
MaterialLibaryLoader* MaterialLibaryLoader::_instance = nullptr;
ID3D11Device* MaterialLibaryLoader::_device = nullptr;
ID3D11DeviceContext* MaterialLibaryLoader::_deviceContext = nullptr;


MaterialLibaryLoader::MaterialLibaryLoader()
{
}


MaterialLibaryLoader::~MaterialLibaryLoader()
{
}

Libary* MaterialLibaryLoader::LoadMtl(std::string filepath)
{
	std::ifstream inFile(filepath, std::ifstream::in);

	std::string textReadIn;

	Libary* Return = new Libary;
	Return->LibaryName = filepath;
	int MaterialCount;


	std::vector<MaterialOld*> loadedMaterials;



	int i = -1;
	while(std::getline(inFile, textReadIn))
	{
		if (textReadIn.length() >= 1)
		{
			if (textReadIn.substr(0, 6) == "newmtl")
			{
				i++;
				Return->MaterialCount++;
				loadedMaterials.push_back(new MaterialOld());

				loadedMaterials.at(i)->MaterialName = textReadIn.substr(7, textReadIn.length() - 1);
			}
		
			if (textReadIn.substr(0, 3) == "\tNs")
			{
				loadedMaterials.at(i)->Ns = stof(textReadIn.substr(3, textReadIn.length() - 1));
			}
			else if (textReadIn.substr(0, 3) == "\tNi")
			{
				loadedMaterials.at(i)->Ni = stof(textReadIn.substr(3, textReadIn.length() - 1));
			}
			else if (textReadIn.substr(0, 2) == "\td")
			{
				loadedMaterials.at(i)->d = stof(textReadIn.substr(3, textReadIn.length() - 1));
			}
			else if (textReadIn.substr(0, 3) == "\tTr")
			{
				loadedMaterials.at(i)->Tr = stof(textReadIn.substr(3, textReadIn.length() - 1));
			}
			else if (textReadIn.substr(0, 3) == "\tTf")
			{
				loadedMaterials.at(i)->Tf[0] = stof(textReadIn.substr(3, textReadIn.find(" ", 4)));
				loadedMaterials.at(i)->Tf[1] = stof(textReadIn.substr(textReadIn.find(" ", 3), textReadIn.find(" ", textReadIn.find(" ", 3) + 1)));
				loadedMaterials.at(i)->Tf[2] = stof(textReadIn.substr(textReadIn.find(" ", textReadIn.find(" ", 3) + 1), textReadIn.length() - 1));
			}
			else if (textReadIn.substr(0, 6) == "\tillum")
			{
				loadedMaterials.at(i)->illum = stoi(textReadIn.substr(7, textReadIn.length()));
			}
			else if (textReadIn.substr(0, 3) == "\tKa")
			{
				loadedMaterials.at(i)->Ka[0] = stof(textReadIn.substr(3, textReadIn.find(" ", 4)));
				loadedMaterials.at(i)->Ka[1] = stof(textReadIn.substr(textReadIn.find(" ", 4), textReadIn.find(" ", textReadIn.find(" ", 4) + 1)));
				loadedMaterials.at(i)->Ka[2] = stof(textReadIn.substr(textReadIn.find(" ", textReadIn.find(" ", 4) + 1), textReadIn.length() - 1));
			}
			else if (textReadIn.substr(0, 3) == "\tKd")
			{
				loadedMaterials.at(i)->Kd[0] = stof(textReadIn.substr(3, textReadIn.find(" ", 4)));
				loadedMaterials.at(i)->Kd[1] = stof(textReadIn.substr(textReadIn.find(" ", 4), textReadIn.find(" ", textReadIn.find(" ", 4) + 1)));
				loadedMaterials.at(i)->Kd[2] = stof(textReadIn.substr(textReadIn.find(" ", textReadIn.find(" ", 4) + 1), textReadIn.length() - 1));
			}
			else if (textReadIn.substr(0, 3) == "\tKs")
			{
				loadedMaterials.at(i)->Ks[0] = stof(textReadIn.substr(3, textReadIn.find(" ", 4)));
				loadedMaterials.at(i)->Ks[1] = stof(textReadIn.substr(textReadIn.find(" ", 3), textReadIn.find(" ", textReadIn.find(" ", 3) + 1)));
				loadedMaterials.at(i)->Ks[2] = stof(textReadIn.substr(textReadIn.find(" ", textReadIn.find(" ", 4) + 1), textReadIn.length() - 1));
			}
			else if (textReadIn.substr(0, 3) == "\tKe")
			{
				loadedMaterials.at(i)->Ke[0] = stof(textReadIn.substr(3, textReadIn.find(" ", 4)));
				loadedMaterials.at(i)->Ke[1] = stof(textReadIn.substr(textReadIn.find(" ", 4), textReadIn.find(" ", textReadIn.find(" ", 3) + 1)));
				loadedMaterials.at(i)->Ke[2] = stof(textReadIn.substr(textReadIn.find(" ", textReadIn.find(" ", 4) + 1), textReadIn.length() - 1));
			}
			else if (textReadIn.substr(0, 7) == "\tmap_Ka")
			{
				//Ambiant
				loadedMaterials.at(i)->LoadedTextures[0] = new Texture2D(textReadIn.substr(8, textReadIn.find(" ", textReadIn.length() - 1)));
				loadedMaterials.at(i)->LoadedTextures[0]->Initialize();
			}
			else if (textReadIn.substr(0, 7) == "\tmap_Kd")
			{
				//Diffuse
				loadedMaterials.at(i)->LoadedTextures[1] = new Texture2D(textReadIn.substr(8, textReadIn.find(" ", textReadIn.length() - 1)));

				loadedMaterials.at(i)->LoadedTextures[1]->Initialize();


			}
			else if (textReadIn.substr(0, 7) == "\tmap_Ks")
			{
				//Specular
				loadedMaterials.at(i)->LoadedTextures[2] = new Texture2D(textReadIn.substr(8, textReadIn.find(" ", textReadIn.length() - 1)));

				loadedMaterials.at(i)->LoadedTextures[2]->Initialize();

			}
			else if (textReadIn.substr(0, 7) == "\tmap_Ns")
			{
				//Specilar Highlight Component
				loadedMaterials.at(i)->LoadedTextures[3] = new Texture2D(textReadIn.substr(8, textReadIn.find(" ", textReadIn.length() - 1)));

				loadedMaterials.at(i)->LoadedTextures[3]->Initialize();

			}
			else if (textReadIn.substr(0, 6) == "\tmap_d")
			{
				//alpha texture map
				loadedMaterials.at(i)->LoadedTextures[4] = new Texture2D(textReadIn.substr(7, textReadIn.find(" ", textReadIn.length() - 1)));

				loadedMaterials.at(i)->LoadedTextures[4]->Initialize();

			}
			else if (textReadIn.substr(0, 9) == "\tmap_bump")
			{
				//alpha texture map
				loadedMaterials.at(i)->LoadedTextures[5] = new Texture2D(textReadIn.substr(10, textReadIn.find(" ", textReadIn.length() - 1)));

				loadedMaterials.at(i)->LoadedTextures[5]->Initialize();

			}
			else if (textReadIn.substr(0, 5) == "\tbump")
			{
				//alpha texture map
				loadedMaterials.at(i)->LoadedTextures[5] = new Texture2D(textReadIn.substr(6, textReadIn.find(" ", textReadIn.length() - 1)));

				loadedMaterials.at(i)->LoadedTextures[5]->Initialize();

			}
		}
	}

	Return->LoadedMaterials = new MaterialOld*[Return->MaterialCount];
	for (int i = 0; i < Return->MaterialCount; i++)
	{
		Return->LoadedMaterials[i] = loadedMaterials.at(i);
	}
	int j = 0;

	LoadedLibaries.push_back(Return);

	return LoadedLibaries.at(LoadedLibaries.size()-1);
}
