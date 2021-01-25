#ifndef _RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_
#include "../../Utils/Managers/Manager.h"
#include "../../Utils/Singleton.h"
#include "../Resource.h"
#include <vector>
#include <map>

#include "../../File_IO/JsonUtils.h"

typedef std::map<ulong, Resource*> ResourceMap;
typedef std::map<ulong, char*> ResourceLibary;
class ResourceManager : public Manager, public Singleton<ResourceManager>
{
private:
    // links a object name to a ulong resouce pair
    ResourceMap m_resourceMap;
    ResourceLibary m_resourceLibary; //Should be loaded on int. keeps a constant list of all resource file paths (from assets) to ids.
    char* m_resourceLibaryFilePath;
    ulong m_nextID;

    JsonUtils::Json m_assetLibaryFile;
public:
    void Initialise() override;
    void Start() override;
    void Update() override;
    void Release() override;

    //Loads a specific resource
    Resource* LoadResource(char* filepath, ResourceType resourseType);
	Resource* LoadResource(ulong resourceID, ResourceType resourseType);
	Resource* LoadResource(Resource* resource);

    ulong AddResource(Resource* resource);

    //Releases a specific Resource
    void ReleaseResource(ulong resourceID);
    bool ReleaseResource(Resource* resourceID);

    // Releases all resources held
    void ReleaseResources();

    // Returns if a resource has already been loaded
    bool IsResourceLoaded(char* filePath);
    bool IsResourceLoaded(ulong resourceID);

    ulong GetResourceID(char* filePath);

    Resource* GetResource(char* filePath);
    Resource* GetResource(ulong resourceID);

    char* GetFilePath(ulong resourceID);
};

#endif //!_RESOURCE_MANAGER_H_