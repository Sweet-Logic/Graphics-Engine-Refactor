#include "ResourceManager.h"
#include "../../File_IO/FileParser.h"
#include "../../Utils/String/StringUtils.h"
#include <exception>

#include "../Textures/Texture2DFactory.h"

#include "../Mesh/StaticMeshFactory.h"
#include "../Materials/MaterialFactory.h"
#include "../Scene/SceneFactory.h"
#include "../../File_IO/JsonUtils.h"

using namespace JsonUtils;

void ResourceManager::Initialise()
{
    m_assetLibaryFile.ReadFromFile("ProjectSettings/AssetLibary.json");

    ArrayElement* assets = static_cast<ArrayElement*>(m_assetLibaryFile.Find("Assets"));
    
    ulong id;
    char* name;
    ResourceType type;
    char* path;
    ArrayElement* asset;
    for(std::vector<JsonElement*>::size_type i = 0; i < assets->elements.size(); ++i)
    {
        asset = static_cast<ArrayElement*>(assets->elements[i]);
        id = StrUtils::stoul(static_cast<ValueElement*>(asset->elements[0])->element);
        name = static_cast<ValueElement*>(asset->elements[1])->element;
        type = (ResourceType)StrUtils::stoi(static_cast<ValueElement*>(asset->elements[2])->element);
        path = static_cast<ValueElement*>(asset->elements[3])->element;
        
        Resource* newResource;
        switch(type)
        {
            case ResourceType::E_BASIC_MATERIAL:
				newResource = new Material();
 				break;
            case ResourceType::E_STATIC_MESH:
				newResource = new StaticMesh();
				break;
            case ResourceType::E_TEXTURE2D:
				newResource = new Texture2D();
				break;
			case ResourceType::E_SCENE:
				newResource = new Scene();
				break;
            case ResourceType::E_SHADER:
                //newResource = 
                break;
            case ResourceType::E_RESOURCE:
            // Type is not inheriting from resource
				break;
            default:
				break;
                //type is not a resource
		};
        if(newResource)
        {
            newResource->SetID(id);
            newResource->SetFilePath(path);
            newResource->SetIsLoaded(false);
            newResource->SetName(name);
            AddResource(newResource);
        }
    }

}

void ResourceManager::Start() 
{

}

void ResourceManager::Update() 
{

}

void ResourceManager::Release()
{
    ReleaseResources();
}


Resource* ResourceManager::LoadResource(char* filePath, ResourceType resourseType)
{
    if(!IsResourceLoaded(filePath))
    {
        unsigned int pathLength = StrUtils::GetLength(filePath);
        int extStart = StrUtils::rFind(filePath, '.');
        int fileNameStart = StrUtils::rFind(filePath, '\\');
        if(fileNameStart == -1)
        {
            fileNameStart = StrUtils::rFind(filePath, '/');
        }
		++fileNameStart;
        char* fileName = StrUtils::copy(filePath,fileNameStart, extStart-fileNameStart);
		Resource* resource;
        switch(resourseType)
        {
            case ResourceType::E_BASIC_MATERIAL:
				resource = MATERIAL_FACTORY::Create(filePath);
				break;
            case ResourceType::E_STATIC_MESH:
				resource = STATIC_MESH_FACTORY::Create(filePath);
				break;
            case ResourceType::E_TEXTURE2D:
				resource = TEXTURE_2D_FACTORY::Create(filePath);
				break;
			case ResourceType::E_SCENE:
				resource = SCENE_FACTORY::Create(filePath);
				break;
            case ResourceType::E_RESOURCE:
            // Type is not inheriting from resource
				break;
            default:
                resource = nullptr;
                printf("Error | Could not load resource with mask of %#x!", resourseType);
                return nullptr;
				break;
                //type is not a resource
		};
        if (nullptr == resource)
        {
            resource->SetFilePath(filePath);
            resource->SetID(m_nextID);
            resource->SetIsLoaded(true);
            resource->SetName(fileName);
            resource->SetType(resourseType);
            AddResource(resource);
            ++m_nextID;
        }
		return resource;
    }
    else
    {
		Resource* resource = GetResource(filePath);
        if(resource)
        {
            return resource;
        }
        //Error resource is either null or not of type
        //Check file extention
        //  If the right extention then the resource is not loaded
        //  else the extention is not of type
    }
    

    return nullptr;
}

Resource* ResourceManager::LoadResource(ulong resourceID, ResourceType resourseType)
{
	if (!IsResourceLoaded(resourceID))
	{
		ResourceLibary::iterator it = m_resourceLibary.find(resourceID);
		char* filePath;
		if (it != m_resourceLibary.end())
		{
			filePath = it->second;
		}
		else
		{
			//Resource is not in the libary!
		}
		unsigned int pathLength = StrUtils::GetLength(filePath);
		int extStart = StrUtils::rFind(filePath, '.');
		int fileNameStart = StrUtils::rFind(filePath, '\\');
		if (fileNameStart == -1)
		{
			fileNameStart = StrUtils::rFind(filePath, '/');
		}

		char* fileName = StrUtils::copy(filePath, fileNameStart, extStart - fileNameStart);
		Resource* resource;
		switch (resourseType)
		{
			case ResourceType::E_BASIC_MATERIAL:
				resource = MATERIAL_FACTORY::Create(filePath);
				break;
			case ResourceType::E_STATIC_MESH:
				resource = STATIC_MESH_FACTORY::Create(filePath);
				break;
			case ResourceType::E_TEXTURE2D:
				resource = TEXTURE_2D_FACTORY::Create(filePath);
				break;
			case ResourceType::E_SCENE:
				resource = SCENE_FACTORY::Create(filePath);
				break;
			case ResourceType::E_RESOURCE:
				// Type is not inheriting from resource
				break;
			default:
				break;
			//type is not a resource
		};

		resource->SetFilePath(filePath);
		resource->SetID(m_nextID);
		resource->SetIsLoaded(true);
		resource->SetName(fileName);
		resource->SetType(resourseType);
		AddResource(resource);
		++m_nextID;
		return resource;
	}
	else
	{
		Resource* resource = GetResource(resourceID);
		if (resource)
		{
			return resource;
		}
		//Error resource is either null or not of type
		//Check file extention
		//  If the right extention then the resource is not loaded
		//  else the extention is not of type
	}
	return nullptr;
}

Resource* ResourceManager::LoadResource(Resource* resource)
{
	if (!resource->IsLoaded())
	{
		switch (resource->GetType())
		{
			case ResourceType::E_BASIC_MATERIAL:
				resource = MATERIAL_FACTORY::Create(resource);
				break;
			case ResourceType::E_STATIC_MESH:
				resource = STATIC_MESH_FACTORY::Create(resource);
				break;
			case ResourceType::E_TEXTURE2D:
				resource = TEXTURE_2D_FACTORY::Create(resource);
				break;
			case ResourceType::E_SCENE:
				resource = SCENE_FACTORY::Create(resource);
				break;
			case ResourceType::E_RESOURCE:
				// Type is not inheriting from resource
				break;
			default:
				break;
			//type is not a resource
		};
		return resource;
	}
	else
	{
		return resource;
		//Error resource is either null or not of type
		//Check file extention
		//  If the right extention then the resource is not loaded
		//  else the extention is not of type
	}
	return nullptr;
}


ulong ResourceManager::AddResource(Resource* resource)
{   
    ulong id = resource->GetID();
    if(id == ULONG_MAX)
    {
        if(m_nextID != ULONG_MAX)
        {
            id = m_nextID;
            resource->SetID(id);
        }
        else
        {
            //HUH How many objects do we need.
        }
    }
    if(m_resourceMap.find(resource->GetID()) == m_resourceMap.end())
    {
        m_resourceMap.insert({resource->GetID(), resource});
    }
	return resource->GetID();
}

void ResourceManager::ReleaseResource(ulong resourceID)
{
    try
    {
        ResourceMap::iterator it = m_resourceMap.find(resourceID);
        if(it != m_resourceMap.end())
        {
            if(ReleaseResource(it->second))
            {
                m_resourceMap.erase(it);
                return;
            }
            throw(new std::exception("Failed to release resource!"));
            //failed to release resource
            //DEBUG FAILED TO RELEASE RESOURCE  
        }
        throw(new std::exception("Resource does not exist within resource map"));
        //element does not exsist in map
    }
    catch(std::exception e)
    {
        _ASSERT(false, "Error whilst Releasing Resources: " + e.what());
        //TODO::DEBUG(e.what(), DEBUG_TYPE::ERROR);
    }
}

bool ResourceManager::ReleaseResource(Resource* resourceID)
{
    try
    {
        
    }
    catch(std::exception e)
    {
        _ASSERT(false, "Error whilst Releasing Resources: " + e.what());
        //TODO::DEBUG(e.what(), DEBUG_TYPE::ERROR);
		return false;
    }
	return true;    
}

void ResourceManager::ReleaseResources()
{
    int i = -1;
    ResourceMap::iterator it = m_resourceMap.begin();
    while(it != m_resourceMap.end())
    {
        ReleaseResource(it->second);
		++it;
    }
    m_resourceMap.clear();
}

bool ResourceManager::IsResourceLoaded(char* filePath)
{
    ulong resourceID = GetResourceID(filePath);
    return IsResourceLoaded(resourceID);
}

bool ResourceManager::IsResourceLoaded(ulong resourceID)
{
    return m_resourceMap.find(resourceID) != m_resourceMap.end();
}

ulong ResourceManager::GetResourceID(char* filePath)
{
    ResourceLibary::iterator it = m_resourceLibary.begin();
    while(it != m_resourceLibary.end())
    {
        if(StrUtils::Compare(filePath, it->second))
        {
            return it->first;
        }
    }
    return ULONG_MAX;
}
char* ResourceManager::GetFilePath(ulong resourceID)
{
    ResourceLibary::iterator it = m_resourceLibary.find(resourceID);
    if(it != m_resourceLibary.end())
    {
        return it->second;
    }
    return nullptr;
}

Resource* ResourceManager::GetResource(ulong resourceID)
{
    ResourceMap::iterator it = m_resourceMap.find(resourceID);
    if(it == m_resourceMap.end())
    {
		return nullptr;
    }
	return it->second;
}

Resource* ResourceManager::GetResource(char* filePath)
{
	return GetResource(GetResourceID(filePath));
}