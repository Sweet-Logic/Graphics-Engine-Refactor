#include "MeshRenderer.h"    

#include "../../../System/Graphics/Graphics.h"
#include "../../../Resource/Managers/ResourceManager.h"

char* MeshRenderer::GetName() 
{
    return "MeshRenderer";
}

void MeshRenderer::BindMaterials(Mesh* materialsToBind)
{
    ID3D11ShaderResourceView* shaderRSV[Material::MaterialIndex::INDEX_COUNT];

    for(int i = 0; i < Material::MaterialIndex::INDEX_COUNT; ++i)
    {
        shaderRSV[i] = materialsToBind->GetMaterial()->m_materialMaps[i]->GetShaderResourceView();
    }

    m_deviceContextRef->PSSetShaderResources(0, 1, shaderRSV);
}  

void MeshRenderer::BindBuffers(Mesh* meshToBind)
{
    m_deviceContextRef->IASetVertexBuffers(0, 1, meshToBind->GetVertexBuffer(), meshToBind->GetVertexStride(),meshToBind->GetVertexOffset());
    m_deviceContextRef->IASetIndexBuffer(meshToBind->GetIndexBuffer(), DXGI_FORMAT_R16_UINT, 0);
}  

void MeshRenderer::Draw()
{
    ID3D11DeviceContext* m_context = Graphics::GetInstance().GetContext();
    for(unsigned int i = 0; i < m_staticMesh->m_elementCount; ++i)
    {
        Mesh* currentMesh = (m_staticMesh->m_elements[i]);
        BindMaterials(currentMesh);
        BindBuffers(currentMesh);
        m_context->DrawIndexed(currentMesh->GetIndexCount(), currentMesh->GetStartIndex(), currentMesh->GetStartVertex());
    }
}

JsonUtils::JsonElement* MeshRenderer::Serialise() 
{
	JsonUtils::ArrayElement* array = new JsonUtils::ArrayElement();

    std::stringstream ss;
	{
		ss << m_staticMesh->GetID();
		const std::string& tmp = ss.str();
		char* chara = new char[tmp.length() + 1];
		tmp.copy(chara, tmp.length());
		chara[tmp.length()] = '\0';
		array->elements.push_back(new JsonUtils::ValueElement("StaticMesh", chara));
		ss.str("");
	}

	{
		ss << (int)GetTopology();
		const std::string& tmp = ss.str();
		char* chara = new char[tmp.length() + 1];
		tmp.copy(chara, tmp.length());
		chara[tmp.length()] = '\0';
		array->elements.push_back(new JsonUtils::ValueElement("RenderWireframe", chara));
		ss.str("");
	}

	{
		ss << RenderWireframe();
		const std::string& tmp = ss.str();
		char* chara = new char[tmp.length() + 1];
		tmp.copy(chara, tmp.length());
		chara[tmp.length()] = '\0';
		array->elements.push_back(new JsonUtils::ValueElement("Topology", chara));
		ss.str("");
	}    
    return array;
}

void MeshRenderer::Deserialise(JsonUtils::JsonElement* object) 
{
    JsonUtils::ArrayElement* array = static_cast<JsonUtils::ArrayElement*>(object);

    JsonUtils::ValueElement* element = static_cast<JsonUtils::ValueElement*>(array->elements[0]);

    std::stringstream ss = std::stringstream(element->element);
    ulong resourceID = ULONG_MAX;
    ss >> resourceID;
    if(resourceID != ULONG_MAX)
    {
        ResourceManager& alias = ResourceManager::GetInstance();

		StaticMesh* staticMesh = nullptr;
		if (alias.IsResourceLoaded(resourceID))
		{
			m_staticMesh = static_cast<StaticMesh*>(alias.GetResource(resourceID));
		}
		else
		{
			m_staticMesh = static_cast<StaticMesh*>(alias.LoadResource(resourceID, E_STATIC_MESH));
		}
    }

	int topo;
	ss >> topo;
	m_topology = (D3D11_PRIMITIVE_TOPOLOGY)topo;

	ss >> m_renderWireframe;
}
