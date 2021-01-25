#include "ShaderManager.h"

#include <d3d11_1.h>
#include <d3dcompiler.h>

#include "../../File_IO/DirectoryService.h"
#include "../../File_IO/JsonUtils.h"
#include "../../Utils/String/StringUtils.h"

#include "../../Resource/Managers/ResourceManager.h"
#include "Graphics.h"


#define BIND_SHADER( type, func ) 						\
	{													\
		type* shader = static_cast<type*>(shaderToBind);\
		if(shader != nullptr)   						\
		{ 												\
			func(shader->m_DX11Shader, nullptr, 0); 	\
			return; 									\
		} 												\
	}													\


#define CompileShaders(FilePath, Entry, version, type, func, shaderArr, currIndex)														\
        type* newShader = new type();																									\
        HRESULT hr = CompileShaderFromFile(FilePath, Entry, version, &newShader->m_blob);												\
        hr =    func(newShader->m_blob->GetBufferPointer(), newShader->m_blob->GetBufferSize(), nullptr, &(newShader->m_DX11Shader));	\
        if (FAILED(hr))                                                                                                                 \
        {                                                                                                                               \
            MessageBox(nullptr,                                                                                                         \
                L"The Shader Could not be created", L"Error", MB_OK);                                                                   \
            return hr;                                                                                                                  \
        }                                                                                                                               \
        shaderArr[currentIndex] = newShader;																							\
        ++(*currIndex);


using namespace StrUtils;

char* ShaderManager::s_shaderAssetFolderLocation = "\\Shader";

void ShaderManager::Initialise()
{
    m_graphicsInstance = &Graphics::GetInstance();
    m_pImmediateContext = m_graphicsInstance->GetContext();
    m_pDevice = m_graphicsInstance->GetDevice();

    m_baseShadingModel = new BaseShading();
    m_shadowMappingModel = new ShadowMap();
	m_finalRender = new FinalRender();
	float w, h;
	w = Window::GetInstance().GetWidth();
	h = Window::GetInstance().GetHight();
	m_baseShadingModel->SetSize(w, h);
	m_shadowMappingModel->SetSize(w, h);
	m_finalRender->SetSize(w, h);
	m_baseShadingModel->Initialise();
    m_shadowMappingModel->Initialise();
	m_finalRender->Initialise();
}

void ShaderManager::Start()
{

}

void ShaderManager::Update()
{

}

void ShaderManager::Release()
{
    std::map<int, std::pair<char*, ShaderGroup*>>::iterator it = m_shaderList.begin();
    if(it != m_shaderList.end())
    {
        do
        {
            for(int i = 0; i < MAX_SHADER_COUNT; ++i)
            {
                ResourceManager::GetInstance().ReleaseResource(it->second.second->m_shaders[i]);
            }
            it->second.second->m_rendersUsingShader.clear();
            delete it->second.first;
            ++it;
        } while(it != m_shaderList.end());
    }

    m_shaderList.clear();
}

void ShaderManager::ReadShaderGroupFile()
{
    /*JsonUtils::Json json;
    json.ReadFromFile(
        Append(
            DirectoryService::GetInstance().GetAssetFileDirectory(),
            s_shaderAssetFolderLocation
        )
    );*/

   /* JsonUtils::ArrayElement* file = static_cast<JsonUtils::ArrayElement*>(json.m_document);

    int groupCount = stoi(static_cast<JsonUtils::ValueElement*>(file->elements[0])->element);
    JsonUtils::ArrayElement* shaderGroups = static_cast<JsonUtils::ArrayElement*>(file->elements[1]);
    
    ShaderType types[6] = 
    {
      	E_VERTEX,
        E_HULL,
        E_DOMAIN,
        E_GEOMETRY,
        E_PIXEL,
        E_COMPUTE
    };

    for(int i = 0; i < groupCount; ++i)
    {
        JsonUtils::ArrayElement* shaderGroup = static_cast<JsonUtils::ArrayElement*>(shaderGroups->elements[i]);

        ShaderGroup* group = new ShaderGroup();
        char* groupName = static_cast<JsonUtils::ValueElement*>(shaderGroup->elements[0])->element;
        JsonUtils::ArrayElement* shaders = static_cast<JsonUtils::ArrayElement*>(shaderGroup->elements[1]);

        for(int j = 0; j < MAX_SHADER_COUNT; ++j)
        {
            char* path = static_cast<JsonUtils::ValueElement*>(shaders->elements[0])->element;
            if(GetLength(path) > 0)
            {
                group->m_shaders[j] = LoadShader(path,types[j]);
            }
        }
        m_shaderList.emplace(i, std::make_pair(groupName, group));
    }*/
}

bool ShaderManager::AssignRendererToGroup(MeshRenderer* renderer, int groupID)
{
    std::map<int, std::pair<char*, ShaderGroup*>>::iterator it = m_shaderList.find(groupID);
    if(it != m_shaderList.end())
    {
        it->second.second->m_rendersUsingShader.push_back(renderer);
        return true;
    }
    //error could not find item in map
    return false;
}

int ShaderManager::GetGroupIDfromName(char* groupName)
{
    std::map<int, std::pair<char*, ShaderGroup*>>::iterator it = m_shaderList.begin();
    do
    {
        if(Compare(it->second.first, groupName))
        {
            return it->first;
        }
        ++it;
    } while(it != m_shaderList.end());

    return -1;
}


Shader* ShaderManager::LoadShader(char* filePath, ShaderType shaderToLoad)
{
    return static_cast<Shader*>(ResourceManager::GetInstance().LoadResource(filePath, E_SHADER));
}



void ShaderManager::ReloadShaders()
{

}


void ShaderManager::Draw()
{
    //Check if pre process is needed
    //Set up Pre Process
    //Run Pre process
    Pre();
    
    //Set up main process
    //Run main process  
    Main();
    //Check if post process is needed
    //Set up post process
    //run post process

    //set up UI process
    //run ui process
	

	Final();
    float deltaTime = 0.033f;

    // std::map<int, std::pair<char*, ShaderGroup*>>::iterator it = m_shaderList.begin();
    // if(it != m_shaderList.end())
    // {
    //     do
    //     {
    //         ShaderGroup* group = it->second.second;
    //         for(int i = 0; i < MAX_SHADER_COUNT; ++i)
    //         {
    //             Shader* shader = group->m_shaders[i];
    //             ShaderType type = group->m_shaders[i]->m_type;
    //             BindShader(shader);
    //         }
    //         for(int j = 0; j < group->m_rendersUsingShader.size(); ++j)
    //         {
    //             group->m_rendersUsingShader[j]->Draw();
    //         }
    //         ++it;
    //     } while(it != m_shaderList.end());
    // }
    m_graphicsInstance->GetSwapChain()->Present(0,0);
}

void ShaderManager::Pre()
{
    //Shadow Mapping
    m_shadowMappingModel->SetUp();
    m_shadowMappingModel->Execute();
    m_shadowMappingModel->CleanUp();

}

void ShaderManager::Main()
{
    //
    m_baseShadingModel->SetUp();
    m_baseShadingModel->Execute();
    m_baseShadingModel->CleanUp();
}

void ShaderManager::Post()
{
    //Post process effects
}

void ShaderManager::UI()
{
    //Drawing UI in screen space
}
void ShaderManager::Final()
{
    m_finalRender->SetUp();
    m_finalRender->Execute();
    m_finalRender->CleanUp();
}

void ShaderManager::BindShader(Shader* shaderToBind)
{
	switch(shaderToBind->m_type)
	{
		case E_VERTEX:
			BIND_SHADER(VertexShader, m_pImmediateContext->VSSetShader)
			break;
		case E_HULL:
			BIND_SHADER(HullShader, m_pImmediateContext->HSSetShader)
			break;
		case E_DOMAIN:
			BIND_SHADER(DomainShader, m_pImmediateContext->DSSetShader)
			break;
		case E_GEOMETRY:
			BIND_SHADER(GeometryShader, m_pImmediateContext->GSSetShader)
			break;
		case E_PIXEL:
			BIND_SHADER(PixelShader, m_pImmediateContext->PSSetShader)
			break;
		case E_COMPUTE:
			BIND_SHADER(ComputeShader, m_pImmediateContext->CSSetShader)
			break;
	}
	//ERROR FAILED TO BIND SHADER
}

HRESULT ShaderManager::LoadShaders(Shader *arrayOfShaders[], unsigned int arrayCount, WCHAR* FilePath, ShaderType shaderTypes)
{
    int currentIndex = 0;
    if((shaderTypes & E_VERTEX) != 0)
    {
	    CompileShaders(FilePath, "VS", "vs_4_0", VertexShader, m_pDevice->CreateVertexShader, arrayOfShaders, &currentIndex)
    }

    if((shaderTypes & E_HULL) != 0)
    {
	    CompileShaders(FilePath, "HS", "hs_4_0", HullShader, m_pDevice->CreateHullShader, arrayOfShaders, &currentIndex)
    }

    if((shaderTypes & E_DOMAIN) != 0)
    {
	    CompileShaders(FilePath, "DS", "ds_4_0", DomainShader, m_pDevice->CreateDomainShader, arrayOfShaders, &currentIndex)
    }

    if((shaderTypes & E_GEOMETRY) != 0)
    {
	    CompileShaders(FilePath, "GS", "gs_4_0", GeometryShader, m_pDevice->CreateGeometryShader, arrayOfShaders, &currentIndex)
    }

    if((shaderTypes & E_PIXEL) != 0)
    {
	    CompileShaders(FilePath, "PS", "ps_4_0", PixelShader, m_pDevice->CreatePixelShader, arrayOfShaders, &currentIndex)
    }

    if((shaderTypes & E_COMPUTE) != 0)
    {
	    CompileShaders(FilePath, "CS", "cs_4_0", ComputeShader, m_pDevice->CreateComputeShader, arrayOfShaders, &currentIndex)
    }
}

HRESULT ShaderManager::CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(DEBUG) || defined(_DEBUG)
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob* pErrorBlob;
	hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel,
		dwShaderFlags, 0, ppBlobOut, &pErrorBlob);

	if (FAILED(hr))
	{
		if (pErrorBlob != nullptr)
			OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());

		if (pErrorBlob) pErrorBlob->Release();

        MessageBox(nullptr,
            L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);

		return hr;
	}

	if (pErrorBlob) pErrorBlob->Release();
	return S_OK;
}

void ShaderManager::ReleaseChild(ID3D11DeviceChild* deviceChild)
{
    if(deviceChild)
        deviceChild->Release();
}
