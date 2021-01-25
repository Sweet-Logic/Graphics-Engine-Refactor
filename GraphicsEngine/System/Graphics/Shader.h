#ifndef _SHADER_H_
#define _SHADER_H_
#ifndef MAX_SHADER_COUNT
#define MAX_SHADER_COUNT 6
#endif

#include <d3d11_1.h>
#include "../../Resource/Resource.h"


enum ShaderType
{
	E_VERTEX = 0x01,
	E_HULL = 0x02,
	E_DOMAIN = 0x04,
	E_GEOMETRY= 0x08,
	E_PIXEL = 0x10,
	E_COMPUTE = 0x20,
};

//Should be a resource.
struct Shader : public Resource
{
	Shader(ShaderType _type):Resource(ResourceType::E_SHADER), m_type(_type) {}
	ID3DBlob* m_blob = nullptr;

	ShaderType m_type;
};

struct VertexShader : public Shader
{
	VertexShader() : Shader(E_VERTEX){};
    ID3D11InputLayout* m_inputLayout;
	ID3D11VertexShader* m_DX11Shader = nullptr;
};

struct HullShader : public Shader
{
	HullShader(): Shader(E_HULL){};
	ID3D11HullShader* m_DX11Shader;
};

struct DomainShader : public Shader
{
	DomainShader(): Shader(E_DOMAIN){};
	ID3D11DomainShader* m_DX11Shader;
};

struct GeometryShader : public Shader
{
	GeometryShader(): Shader(E_GEOMETRY){};
	ID3D11GeometryShader* m_DX11Shader = nullptr;
};

struct PixelShader : public Shader
{
	PixelShader(): Shader(E_PIXEL){};
	ID3D11PixelShader*	m_DX11Shader = nullptr;
};

struct ComputeShader : public Shader
{
	ComputeShader(): Shader(E_COMPUTE){};
	ID3D11ComputeShader* m_DX11Shader;
};


#endif //!_SHADER_H_