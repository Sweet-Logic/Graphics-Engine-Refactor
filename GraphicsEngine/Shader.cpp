#include "Shader.h"
#include <fstream>
#include <d3dcompiler.h>


Shader::Shader(WCHAR* FilePath, LPCSTR vs_EntryPoint, LPCSTR ps_EntryPoint, LPCSTR vs_ShaderModel, LPCSTR ps_ShaderModel, ID3D11Device* Device, ID3DBlob** pVSBlob, ID3DBlob** pPSBlob)
{
	_vertexShader = nullptr;
	_pixelShader = nullptr;
	HRESULT hr = LoadShader(FilePath, vs_EntryPoint, ps_EntryPoint, vs_ShaderModel, ps_ShaderModel, *&Device, &*pVSBlob, &*pPSBlob);
}


Shader::~Shader()
{
}

HRESULT Shader::LoadShader(WCHAR* FilePath, LPCSTR vs_EntryPoint, LPCSTR ps_EntryPoint, LPCSTR vs_ShaderModel, LPCSTR ps_ShaderModel, ID3D11Device* Device, ID3DBlob** pVSBlob, ID3DBlob** pPSBlob)
{

	HRESULT hr = CompileShaderFromFile(FilePath, vs_EntryPoint, vs_ShaderModel, &*pVSBlob);

	if (FAILED(hr))
	{
		MessageBox(nullptr,
			L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return hr;
	}
	
	// Create the vertex shader
	hr = Device->CreateVertexShader((*pVSBlob)->GetBufferPointer(), (*pVSBlob)->GetBufferSize(), nullptr, &_vertexShader);

	if (FAILED(hr))
	{
		MessageBox(nullptr,
			L"The Shader Could not be created", L"Error", MB_OK);
		return hr;
	}


	if (ps_EntryPoint != "")
	{
		// Compile the pixel shader
		hr = CompileShaderFromFile(FilePath, ps_EntryPoint, ps_ShaderModel, &(*pPSBlob));

		if (FAILED(hr))
		{
			MessageBox(nullptr,
				L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
			return hr;
		}

	
		// Create the pixel shader
		hr = Device->CreatePixelShader((*pPSBlob)->GetBufferPointer(), (*pPSBlob)->GetBufferSize(), nullptr, &_pixelShader);
		(*pPSBlob)->Release();

		if (FAILED(hr))
		{
			MessageBox(nullptr,
				L"The Shader Could not be created", L"Error", MB_OK);
			return hr;
		}
	}

}

HRESULT Shader::CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
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

		return hr;
	}

	if (pErrorBlob) pErrorBlob->Release();

	return S_OK;
}