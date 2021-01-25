#include "SceneManager.h"

#include "../Utils/String/StringUtils.h"

#include "../Object/Components/Transform.h"
#include "../Resource//Managers//ResourceManager.h"
#include "../Resource/Scene/Scene.h"
#include "../Resource\Scene\SceneFactory.h"
#include "../File_IO/DirectoryService.h"


void SceneManager::LoadScene(int sceneID) 
{
    //Get the file path for the scene
    Scene* sceneToLoad;
    SceneLibary::iterator it = m_sceneLibary.find(sceneID);

    _ASSERT_EXPR(it != m_sceneLibary.end(), "the Scene ID Does not exist within the libary");

    sceneToLoad = static_cast<Scene*>(ResourceManager::GetInstance().GetResource(m_sceneLibary.at(sceneID).first));

    if(sceneToLoad != nullptr)
    {
        m_primaryActiveScene = sceneID;
        m_currentScene = sceneToLoad;
		m_sceneFile.ReadFromFile(DirectoryService::GetInstance().ReplaceDirectoryTags(sceneToLoad->GetFilePath()));
		
		std::vector<JsonUtils::JsonElement*> objectArray = static_cast<JsonUtils::ArrayElement*>(m_sceneFile.Find("Objects"))->elements;
		for (std::vector<JsonUtils::JsonElement*>::size_type i = 0; i < objectArray.size(); ++i)
		{
			GameObject* newObject = CreateNewObject();
			newObject->Deserialise(objectArray[i]);
			m_sceneGraph.Add(newObject);
		}


		m_sceneFile;
        return;
    }
    //Failed to load the scene
}

GameObject* SceneManager::CreateNewObject()
{
    GameObject* newObject = new GameObject();
    m_sceneGraph.Add(newObject);    
	m_currentScene->SetDirty(true);
	return newObject;
}

void SceneManager::SaveScene(int m_sceneID)
{
    if(m_currentScene->m_isDirty == true)
    {
        //Write all scene objects to the structure
        JsonUtils::Json file;

        JsonUtils::ArrayElement* array = new JsonUtils::ArrayElement[3];
		array->elements.push_back(new JsonUtils::ValueElement("Type", "SCENE"));
		array->elements.push_back(new JsonUtils::ValueElement("Name", m_currentScene->GetName()));
		array->elements.push_back(new JsonUtils::ValueElement("ResourceID", StrUtils::ToString(m_currentScene->GetID())));
		JsonUtils::ArrayElement* objectArray = new JsonUtils::ArrayElement();
		objectArray->tag = "Objects";
        SceneGraph::Node* curr = m_sceneGraph.GetHead();
		for (int i = 0; curr != nullptr; ++i)
		{
			objectArray->elements.push_back(curr->value->Serialise());
			curr = curr->A;
		}
		array->elements.push_back(objectArray);

        file.m_document = array;
		

		if (file.WriteToFile(m_currentScene->GetFilePath()))
		{
			m_currentScene->SetDirty(false);
		}
    }
}

void SceneManager::ReleaseScene(int sceneID) 
{
    //Go through the scene graph and release all the base objects. this should release all child objects releasing all memory being used.
    SceneGraph::Node* curr;
    while (m_sceneGraph.GetHead())
    {
        curr = m_sceneGraph.GetHead();
        delete m_sceneGraph.GetHead()->value;
        m_sceneGraph.RemoveNode(m_sceneGraph.GetHead());
    }    
}

bool SceneManager::IsValidScene(int sceneID)
{
    SceneLibary::iterator it = m_sceneLibary.find(sceneID);

    return it != m_sceneLibary.end();
}


void SceneManager::SwitchScene(int sceneID)
{
	if (IsValidScene(sceneID))
	{
		if (m_primaryActiveScene != -1)
		{
			//Unload the current active scene
			SaveScene(m_primaryActiveScene);
			ReleaseScene(m_primaryActiveScene);
		}
		LoadScene(sceneID);
	}
}

int SceneManager::GetSceneID(char* filePath) 
{
    SceneLibary::iterator it = m_sceneLibary.begin();
    while(it != m_sceneLibary.end())
    {
        if(StrUtils::Compare(filePath, it->second.second))
        {
            return it->second.first;
        }
    }
    return -1;
}

int SceneManager::GetSceneID(Scene *scene)
{
    return scene->GetID();
}

Scene* SceneManager::GetActiveScene()
{
    return m_currentScene;
}

void SceneManager::Initialise() 
{
    
    //Parse the scene list file
    m_libaryFile.ReadFromFile("projectSettings/SceneList.json");

    int defaultScene = StrUtils::stoui(static_cast<JsonUtils::ValueElement*>(m_libaryFile.Find("DefaultScene"))->element);
    JsonUtils::ArrayElement* array = static_cast<JsonUtils::ArrayElement*>(m_libaryFile.Find("Scenes"));
    int sceneID;
    char* name;
    char* filePath;
    Scene* newScene;
    for(std::vector<JsonUtils::JsonElement*>::size_type i = 0; i < array->elements.size(); ++i)
    {
        sceneID = StrUtils::stoui(static_cast<JsonUtils::ValueElement*>(array->elements[i]->RecursiveFind("SceneID"))->element);
        name = static_cast<JsonUtils::ValueElement*>(array->elements[i]->RecursiveFind("Name"))->element;
        filePath = static_cast<JsonUtils::ValueElement*>(array->elements[i]->RecursiveFind("FilePath"))->element;

		newScene = static_cast<Scene*>(ResourceManager::GetInstance().LoadResource(DirectoryService::GetInstance().ReplaceDirectoryTags(filePath), E_SCENE));

        m_sceneLibary.insert(std::make_pair(sceneID, std::make_pair(newScene->GetID(), filePath)));
    }

    //if there is a valid scene
    if(m_sceneLibary.size() > 0)
    {
        LoadScene(defaultScene);
    }
    else
    {
        //Create a blank default scene
		Scene* newScene = CreateDefaultScene();
        m_sceneLibary.insert(std::make_pair(m_sceneLibary.size(), std::make_pair(newScene->GetID(), newScene->GetFilePath())));

		SwitchScene(newScene->GetSceneID());
		m_primaryActiveScene = newScene->GetSceneID();
        m_currentScene = newScene;

        CreateNewObject();

        //Save scene file
		SaveScene(newScene->GetID());
  //      //Save scene to scene list.
  //      LoadScene(newScene->GetID());
    }
    
}

GameObject* SceneManager::GetObjectInScene(int instanceID)
{
    SceneGraph::Node* node = m_sceneGraph.GetHead();
    while (node != nullptr)
    {
        if (node->value->GetID() == instanceID)
        {
            return node->value;
        }
        Transform* transform= GetChildObjectByID(node->value, instanceID);
        if(transform != nullptr)
        {
            return transform->GetGameObject();
        }

        node = node->A;
    }
}

Transform* SceneManager::GetChildObjectByID(GameObject* object, int instanceID)
{
	LinkedList<Transform*> children = object->GetTransform()->GetChildren();

    Transform* child = nullptr;
	LinkedList<Transform*>::Node* node = children.GetHead();
	while (node)
	{
		child = node->value;
		if (child->GetGameObject()->GetID() != instanceID)
		{
			return child;
		}
		child = GetChildObjectByID(child->GetGameObject(), instanceID);
		if (child != nullptr)
		{
			return child;
		}
		node = node->A;
	}
	return nullptr;
}

Scene* SceneManager::CreateDefaultScene()
{
    DirectoryService& alias = DirectoryService::GetInstance();
    char* sceneFilePath = alias.ReplaceDirectoryTags(alias.GetTagPath("Scenes"));

    DirectoryService::GetInstance().GetTagPath("Scenes");
    if(!DirectoryService::GetInstance().DoesFilePathExist(sceneFilePath))
    {
        alias.CreatePath(sceneFilePath);
    }

    char* filePath;
	char* fileName = new char[11]{ "Default_00" };
    do
    {
        fileName[9] = (char)((int)fileName[9] + 1);
		filePath = StrUtils::Append(sceneFilePath, StrUtils::Append(StrUtils::Append("/", fileName), ".json"));
    }while(alias.DoesFileExsist(filePath));
    
	Scene* newScene = SCENE_FACTORY::Create(fileName,m_sceneLibary.size()+1, filePath);
	ResourceManager::GetInstance().AddResource(newScene);
    m_sceneLibary.emplace(newScene->GetSceneID(), std::make_pair(newScene->GetID(), newScene->GetFilePath()));

    JsonUtils::ArrayElement* array = new JsonUtils::ArrayElement();
    std::stringstream ss;
    ss << newScene->GetSceneID();

    array->elements.push_back(new JsonUtils::ValueElement("SceneID", StrUtils::ToString<int>(newScene->GetSceneID())));
    array->elements.push_back(new JsonUtils::ValueElement("Name", fileName));
    array->elements.push_back(new JsonUtils::ValueElement("FilePath", StrUtils::Append("$Scenes$", StrUtils::Append(StrUtils::Append("/", fileName), ".json"))));

    static_cast<JsonUtils::ArrayElement*>(m_libaryFile.Find("Scenes"))->elements.push_back(array);
	static_cast<JsonUtils::ValueElement*>(m_libaryFile.Find("DefaultScene"))->element = StrUtils::ToString<int>(newScene->GetSceneID());

	m_libaryFile.WriteToFile("projectSettings/SceneList.json");
	return newScene;
}

void SceneManager::Start()
{

}

void SceneManager::Update()
{

}

void SceneManager::Release()
{

}