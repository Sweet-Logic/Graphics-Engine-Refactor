//Managers all the shaders in the program!
#ifndef _SHADER_MANAGER_H_
#define _SHADER_MANAGER_H_

#include "../../Utils/Singleton.h"
#include "../../Utils/Managers/Manager.h"
#include "Shader.h"
#include "ShaderGroup.h"

#include "DrawingMethods/BaseShading/BaseShading.h"
#include "DrawingMethods/ShadowTechniques/ShadowMapping.h"
#include "DrawingMethods/FinalRender/FinalRender.h"


#include <vector>
#include <map>

class Graphics;

class ShaderManager;
class RenderTargetView;
class Texture2D;
class ShaderResourceView;
class RenderTargetView;

class ShaderManager : public Singleton<ShaderManager>, public Manager
{
	//Shader Type is the draw order of the shaders.
	static char* s_shaderAssetFolderLocation;
	std::map<int, std::pair<char*, ShaderGroup*>> m_shaderList; // ShaderGroup name to shaderGroup ref

	void ReadShaderGroupFile();

	Shader* LoadShader(char* filePath, ShaderType shaderToLoad);
	bool AssignRendererToGroup(MeshRenderer* renderer, int groupID);

	int GetGroupIDfromName(char* groupName);

	void ReleaseShaders() {};

	void BindShader() {};
	Graphics* m_graphicsInstance;

	void Pre();
	void Main();
	void Post();
	void UI();
	void Final();

	ID3D11DeviceContext*    m_pImmediateContext;
	ID3D11Device* m_pDevice;

	HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

	BaseShading* m_baseShadingModel = nullptr;
	ShadowMap* m_shadowMappingModel = nullptr;
	FinalRender* m_finalRender = nullptr;

	ID3D11ShaderResourceView *pSRV[1] = { NULL };
    ID3D11ShaderResourceView *m_shaderResources[128]; // can have up to 128 srvs per stage
	ID3D11RenderTargetView* m_emptyViews[8] = { nullptr,nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, };

public:
	ID3D11RenderTargetView ** GetEmptyRenderTargets() { return m_emptyViews;}
	ID3D11ShaderResourceView ** GetEmptyShaderResource() { return pSRV;}
	ID3D11ShaderResourceView ** GetResources() { return m_shaderResources;}


	virtual void Initialise() override;
	virtual void Start()override;
	virtual void Update()override;
	virtual void Release()override;
	void Draw();

    void BindShader(Shader* shaderToBind);
	void ReloadShaders();
	void ReleaseChild(ID3D11DeviceChild*);

	HRESULT LoadShaders(Shader *arrayOfShaders[], unsigned int arrayCount, WCHAR* FilePath, ShaderType shaderTypes);

};

#endif //!_SHADER_MANAGER_H_