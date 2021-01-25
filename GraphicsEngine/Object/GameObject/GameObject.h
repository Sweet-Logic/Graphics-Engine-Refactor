#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include <vector>
#include <map>

#include "../../File_IO/Serialising/Serialiseable.h"

class Component;
class Transform;

class GameObject : public Serialiseable
{
public:
	GameObject();
    template <class T>
    T* GetComponent();
    template <class T>
    T* GetComponentInChildren();
    template <class T>
    std::vector<T*> GetComponentsInChildren();

    Transform* const GetTransform() {return &*m_transform;} 

	char* GetName() { return m_objectName; };
	int GetID() { return m_objectID; }

    void SetParent(GameObject& parent);
    void SetName(char* name) {m_objectName = name;};
    void SetID(int id) {m_objectID = id;};

    template <class T>
	T* AddComponent() { T* newComp = new T(); m_componentList.push_back(&*newComp); dynamic_cast<Component*>(newComp)->SetGameObject(this); return &*newComp; };
private:
    char* m_objectName = "Object";
    int m_objectID;
    Transform* m_transform;
    std::vector<Component*> m_componentList;

public: //overrides
    virtual JsonUtils::JsonElement* Serialise() override;
    virtual void Deserialise(JsonUtils::JsonElement* object) override;
};

#endif //!_GAME_OBJECT_H_