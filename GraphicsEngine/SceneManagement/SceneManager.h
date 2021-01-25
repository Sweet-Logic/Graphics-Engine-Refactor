#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_
#include <map>
#include "../Resource/Scene/Scene.h"
#include "../Utils/Managers/Manager.h"
#include "../Utils/Singleton.h"
#include "../Utils/LinkedLists/LinkedLists.h"
#include "../Object/GameObject/GameObject.h"
#include <vector>

typedef unsigned long ulong;

//int needs to be replaced with SceneObjects.
using SceneGraph = LinkedList<GameObject*>;

typedef std::map<int, std::pair<ulong, char*>> SceneLibary;

class SceneManager : public Manager, public Singleton<SceneManager>
{
    SceneLibary m_sceneLibary;//Stores all the scenes that are known
    int m_primaryActiveScene = -1;
    SceneGraph m_sceneGraph;
    Scene* m_currentScene;
    
    char* m_sceneFolderPath = "Assets\\Scenes";

    void LoadScene(int);
    void SaveScene(int);

    void ReleaseScene(int);
    bool IsValidScene(int);
	Scene* CreateDefaultScene();

	JsonUtils::Json m_libaryFile;
	JsonUtils::Json m_sceneFile;

	Transform* GetChildObjectByID(GameObject* object, int instanceID);
    
public:
	SceneGraph const GetSceneGraph() { return m_sceneGraph; };

    GameObject* CreateNewObject();

    void SwitchScene(int);

    int GetSceneID(char*);
    int GetSceneID(Scene*);

    GameObject* GetObjectInScene(int instanceID);

    Scene* GetActiveScene();

    void Initialise()   override;
    void Start()   override;
    void Update()  override;
    void Release() override;
};

#endif //!_SCENE_MANAGER_H_