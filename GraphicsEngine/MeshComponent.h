#pragma once

#include "SceneObject.h"
#include "Texture2D.h"
#include "MaterialLibaryLoader.h"
#include "Buffers.h"
#include <string>


#include <d3d11_1.h>

struct Group
{
	int startIndex;
	int indexCount;
	MaterialOld* mat;
};

class MeshComponent
{
public:
	MeshComponent(std::string filepath) : modelFilePath(filepath) {}
	MeshComponent() {}

	bool Maps[6] = {false, false, false, false, false, false};

	bool HasMap(Map textureMap) { return Maps[textureMap]; }

	~MeshComponent()
	{
		unload();
	}

	void load()
	{
		for (int i = 0; i < Groups; i++)
		{
			if (meshGroups[i].mat)
			{
				for (int j = 0; j < 6; j++)
				{
					if (meshGroups[i].mat->LoadedTextures[j])
					{
						meshGroups[i].mat->LoadedTextures[j]->Initialize();
						Maps[j] = true;

					}
				}
			}
		}
	}

	ID3D11Buffer** GetVertexBuffer() { return &_vertexBuffer; }
	ID3D11Buffer** GetIndexBuffer() { return &_indexBuffer; }

	void InitVertexBuffer(ID3D11Buffer* NewBuffer) {  _vertexBuffer = NewBuffer; }
	void InitIndexBuffer(ID3D11Buffer* NewBuffer) {  _indexBuffer = NewBuffer; }
	int Groups = 1;
	//int* GroupIndicies;

	bool HasTransparancy() { return Maps[Map::Disolved]; }

	Group* meshGroups;

	void Draw(ID3D11DeviceContext*& Context, UINT* stride, UINT* offset, ID3D11Buffer *ConstBuffer , CBObject &ObjectBuffer, bool skipTextures = false)
	{
		Context->IASetVertexBuffers(0, 1, &_vertexBuffer, *&stride, *&offset);
		Context->IASetIndexBuffer(*&_indexBuffer, DXGI_FORMAT_R16_UINT, 0);
		//Context->UpdateSubresource(_CBObject, 0, nullptr, &Object_ConstantBuffer, 0, 0);
		for (int i = 0; i < Groups; i++)
		{
			if (!skipTextures)
			{
				if (meshGroups[i].mat)
				{

					for (int j = 0; j < 6; j++)
					{
						if (Maps[j])
						{
							Context->PSSetShaderResources(j, 1, meshGroups[i].mat->LoadedTextures[j]->GetTexture());

						}
					}
					/*if (meshGroups[i].mat->LoadedTextures[Map::rAmbient])
					{
						Context->PSSetShaderResources(Map::rAmbient, 1, meshGroups[i].mat->LoadedTextures[Map::rAmbient]->GetTexture());

					}
					if (meshGroups[i].mat->LoadedTextures[Map::rDiffuse])
					{
						Context->PSSetShaderResources(Map::rDiffuse, 1, meshGroups[i].mat->LoadedTextures[Map::rDiffuse]->GetTexture());

					}
					if (meshGroups[i].mat->LoadedTextures[Map::rSpecular])
					{
						Context->PSSetShaderResources(Map::rSpecular, 1, meshGroups[i].mat->LoadedTextures[Map::rSpecular]->GetTexture());
					}
					if (meshGroups[i].mat->LoadedTextures[Map::eSpecular])
					{
						Context->PSSetShaderResources(Map::eSpecular, 1, meshGroups[i].mat->LoadedTextures[Map::eSpecular]->GetTexture());
					}
					if (meshGroups[i].mat->LoadedTextures[Map::Disolved])
					{
						Context->PSSetShaderResources(Map::Disolved, 1, meshGroups[i].mat->LoadedTextures[Map::Disolved]->GetTexture());
					}
					if (meshGroups[i].mat->LoadedTextures[Map::Bump])
					{
						Context->PSSetShaderResources(Map::Bump, 1, meshGroups[i].mat->LoadedTextures[Map::Bump]->GetTexture());
					}*/
				}
				else
				{
					// No Texture Maps
				}
			}


//			ObjectBuffer.hasTextureMap = Maps[Map::rDiffuse];
//			ObjectBuffer.hasNormalMap = Maps[Map::Bump];


			Context->UpdateSubresource(ConstBuffer, 0, nullptr, &ObjectBuffer, 0, 0);

			Context->DrawIndexed(meshGroups[i].indexCount, meshGroups[i].startIndex, 0);
		}
	}

	void SetTexture(Map TextureType, Texture2D *newTexture)
	{
		if (meshGroups[0].mat == nullptr)
		{
			meshGroups->mat = new MaterialOld;
			
		}
		meshGroups[0].mat->LoadedTextures[TextureType] = newTexture;
		meshGroups[0].mat->LoadedTextures[TextureType]->Initialize();

		Maps[TextureType] = true;
	}

	void unload()
	{
		_vertexBuffer->Release();
		_indexBuffer->Release();

		for (int i = 0; i < MatLib->MaterialCount; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				
				if (MatLib->LoadedMaterials[i]->LoadedTextures[j])
				{
					delete MatLib->LoadedMaterials[i]->LoadedTextures[j];
				}
			}
			delete MatLib->LoadedMaterials[i];
		}
		delete[] MatLib->LoadedMaterials;
		delete MatLib;
	}

	Libary* MatLib;

	static ID3D11Buffer* _CBObject;
private:
	ID3D11Buffer*	_vertexBuffer = nullptr;
	ID3D11Buffer*	_indexBuffer = nullptr;

	std::string modelFilePath;

};

