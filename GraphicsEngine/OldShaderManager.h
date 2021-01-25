#pragma once

#include "Shader.h"
#include <vector>
#include <string>

class OldShaderManager
{
public:
	~OldShaderManager();

	OldShaderManager* GetInstance() {
		if (_instance)
		{
			return *&_instance;
		}
		return _instance = new OldShaderManager;
	}

	Shader* GetShaderByName(std::string ShaderName)
	{
		

		for (int i = 0; i < _shaderNames.size(); i++)
		{
			if (ShaderName == _shaderNames.at(i))
			{
				return *&_loadedShaders.at(i);
			}
		}

		MessageBox(nullptr,
			L"There was no Shaders loaded matching the name provided.", L"WARNING", MB_OK);

		return nullptr;
	}


	void Release()
	{
		for (int i = 0; i < _loadedShaders.size(); i++)
		{
			_loadedShaders.at(i)->Release();
			delete _loadedShaders.at(i);
			_loadedShaders.erase(_loadedShaders.begin() + i, _loadedShaders.begin() +i + 1);
		}
	}

private:
	std::vector<Shader*> _loadedShaders;
	std::vector<std::string> _shaderNames;

	void LoadShadersFromFile()
	{
		//Load shader paths from a file and shader names
	}

	OldShaderManager* _instance;
	OldShaderManager() {};
};

