#ifndef _SHADER_GROUP_H_
#define _SHADER_GROUP_H_
#include "../../Object/Components/Renderer/MeshRenderer.h"

#include "Shader.h"
#include "../../Resource/Resource.h"

struct ShaderGroup
{
	ShaderGroup() {};
    ShaderType m_types; //Bit mask of the shader groups (Vertex | Pixel)
    Shader* m_shaders[MAX_SHADER_COUNT];// = {nullptr,nullptr,nullptr,nullptr,nullptr,nullptr};
	std::vector<MeshRenderer*> m_rendersUsingShader;
};

#endif //!_SHADER_GROUP_H_