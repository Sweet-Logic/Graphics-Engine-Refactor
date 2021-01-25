#pragma once
#include <string>
#include <d3d11_1.h>


class Shader
{
public:
	Shader(WCHAR* FilePath, LPCSTR vs_EntryPoint, LPCSTR ps_EntryPoint, LPCSTR vs_ShaderModel, LPCSTR ps_ShaderModel, ID3D11Device* Device, ID3DBlob** pVSBlob, ID3DBlob** pPSBlob);
	~Shader();

	

	ID3D11VertexShader*	GetVS()	const { return *&_vertexShader; }
	ID3D11PixelShader*	GetPS()	const { return *&_pixelShader; }

	

	void Release()
	{
		_vertexShader->Release();
		_pixelShader->Release();
		delete this;
	}
protected:


private:
	ID3D11VertexShader* _vertexShader;
	ID3D11PixelShader* _pixelShader;

	HRESULT LoadShader(WCHAR* FilePath, LPCSTR vs_EntryPoint, LPCSTR ps_EntryPoint, LPCSTR vs_ShaderModel, LPCSTR ps_ShaderModel, ID3D11Device* Device, ID3DBlob** pVSBlob, ID3DBlob** pPSBlob);

	HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
};

