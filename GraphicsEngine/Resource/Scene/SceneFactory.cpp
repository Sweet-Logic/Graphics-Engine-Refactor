#include "SceneFactory.h"

#include "../../File_IO/JsonUtils.h"
#include "../../File_IO/DirectoryService.h"
#include <assert.h>

using namespace JsonUtils;
Scene* SCENE_FACTORY::Create(char* filePath)
{
    Scene* loadedScene = new Scene();

    Json file;
	assert(file.ReadFromFile(DirectoryService::GetInstance().ReplaceDirectoryTags(filePath)));

	loadedScene->SetFileInfo(nullptr);
	loadedScene->SetType(E_SCENE);
	loadedScene->SetName(static_cast<ValueElement*>(file.Find("Name"))->element);
	loadedScene->SetID(StrUtils::stoul(static_cast<ValueElement*>(file.Find("ResourceID"))->element));
	loadedScene->SetFilePath(filePath);
	loadedScene->SetIsLoaded(true);
    return loadedScene;
}

Scene* SCENE_FACTORY::Create(char* sceneName,int sceneID, char* filePath)
{
    Scene* loadedScene = new Scene();  
    loadedScene->SetFileInfo(nullptr);
    loadedScene->SetType(E_SCENE);
    loadedScene->SetName(sceneName);
    loadedScene->SetSceneID(sceneID);
    loadedScene->SetFilePath(filePath);
    loadedScene->SetIsLoaded(true);
    return loadedScene;
}

Scene* SCENE_FACTORY::Create(Resource* reosurce)
{
    Scene* loadedScene = static_cast<Scene*>(reosurce);
	loadedScene->SetIsLoaded(true);
    return loadedScene;
}
