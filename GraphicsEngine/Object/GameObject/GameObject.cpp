#include "GameObject.h"
#include "../Components/Transform.h"
#include "../Components/Component.h"

#include <Windows.h>
#define DBOUT( s )            \
{                             \
   std::wostringstream os_;   \
   os_<< '\n';				\
   os_ << s;                   \
   OutputDebugStringW( os_.str().c_str()  );  \
}


GameObject::GameObject()
{
	m_transform = this->AddComponent<Transform>();
}

template <class T>
T*  GameObject::GetComponent()
{
    T *component;
    for(int i = 0; i < m_componentList; ++i)
    {
        component = (dynamic_cast<T>m_componentList[i])
        if(component != nullptr)
        {
            return &component;
        }
    }
}
template <class T>
T*  GameObject::GetComponentInChildren()
{
    LinkedList<GameObject>::Node* currNode = m_transform->m_children;
    if(currNode!= nullptr )
    {
        T* component;
        while(currNode != nullptr)
        {
            component = currNode->value.GetComponent<T>();
            if(component != nullptr)
            {
                return component;
            }
            component = currNode->value.GetComponentInChildren<T>();
            if(component != nullptr)
            {
                return component;
            }
        }
    }
    return nullptr;
}
template <class T>
std::vector<T*>  GameObject::GetComponentsInChildren()
{
    std::vector<T*> result;
    LinkedList<GameObject>::Node* currNode = m_transform->m_children;
    if(currNode!= nullptr )
    {
        std::vector<T*> current;
        T* component;
        while(currNode != nullptr)
        {
            component = currNode->value.GetComponent();
            current = currNode->value.GetComponentsInChildren<T>();
            result.reserve(result.size() + current.size() + (component != nullptr ? 1:0));
            result.insert(result.end(), current.begin(), current.end());
            if(component != nullptr)
            {
                result.push_back(component);
            }
        }
    }
    return result;
}


JsonUtils::JsonElement* GameObject::Serialise()
{
	JsonUtils::ArrayElement* array = new JsonUtils::ArrayElement();

	array->elements.push_back(new JsonUtils::ValueElement("ObjectName", m_objectName));
	array->elements.push_back(new JsonUtils::ValueElement("ObjectID", StrUtils::ToString(m_objectID)));


	JsonUtils::ArrayElement* componentArray = new JsonUtils::ArrayElement();
	componentArray->tag = "Components";
	for (std::vector<Component*>::size_type i = 0; i < m_componentList.size(); ++i)
	{
		JsonUtils::ArrayElement *component = new JsonUtils::ArrayElement();
		component->tag = nullptr;

		component->elements.push_back(new JsonUtils::ValueElement("ComponentType", m_componentList[i]->GetName()));
		JsonUtils::ArrayElement* parameterArray = static_cast<JsonUtils::ArrayElement*>(m_componentList[i]->Serialise());
		parameterArray->tag = "Parameters";
		component->elements.push_back(parameterArray);

		componentArray->elements.push_back(component);
	}
	
	array->elements.push_back(componentArray);
	return array;
}

void GameObject::Deserialise(JsonUtils::JsonElement* object) 
{
    // for each component add it and pass its parameters through.
	JsonUtils::ArrayElement* array = static_cast<JsonUtils::ArrayElement*>(object);

	m_objectName = (static_cast<JsonUtils::ValueElement*>(array->elements[0]))->element;
	m_objectID = StrUtils::stoi((static_cast<JsonUtils::ValueElement*>(array->elements[1]))->element);
	DBOUT("Object: " << m_objectName);
	JsonUtils::ArrayElement* componentArray = static_cast<JsonUtils::ArrayElement*>(array->elements[2]);
	for (std::vector<JsonUtils::JsonElement*>::size_type i = 0; i < componentArray->elements.size(); ++i)
	{
		JsonUtils::ArrayElement* component = static_cast<JsonUtils::ArrayElement*>(componentArray->elements[0]);
		char* componentName = (static_cast<JsonUtils::ValueElement*>(component->elements[0]))->element;
		JsonUtils::ArrayElement* parameterArray = static_cast<JsonUtils::ArrayElement*>(component->elements[1]);

		Component* newComponent = nullptr;
		if (StrUtils::Compare(componentName, "Transform"))
		{
			newComponent = m_transform;
		}

		newComponent->Deserialise(parameterArray);
	}
}