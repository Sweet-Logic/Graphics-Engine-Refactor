#include "Transform.h"
#include "../../File_IO/JsonUtils.h"
#include "../../Utils/String/StringUtils.h"
#include "../../SceneManagement/SceneManager.h"

#include <DirectXMath.h>
using namespace DirectX;

#include <Windows.h>
#define DBOUT( s )            \
{                             \
   std::wostringstream os_;   \
   os_<< '\n';				\
   os_ << s;                   \
   OutputDebugStringW( os_.str().c_str()  );  \
}

XMVECTOR Transform::m_forwardRaw;

void Transform::Start()
{
    m_up = XMVectorSet(0.f,1.f,0.f,0.f);
	m_forwardRaw = XMVectorSet(0.f,0.f,1.f,0.f);
}

void Transform::Update()
{
}

void Transform::PostUpdate()
{
}

void Transform::SetDirty()
{
	m_dirty = true;
	LinkedList<Transform*>::Node *head = m_children.GetHead();
	while(head != nullptr)
	{
		head->value->SetDirty();
		head = head->A;
	}
}


void Transform::SetParent(Transform* parent)
{
	if(m_parent != parent && parent != this)
	{
    	m_parent = parent;
		parent->SetChild(this);
	}
}
void Transform::SetChild(Transform* child)
{
	LinkedList<Transform*>::Node* node = m_children.FindNode(child);
	if(node == nullptr)
	{
		m_children.Add(child);
		if(child->m_parent != this)
		{
			child->SetParent(this);
		}
		return;
	}
	//Some how a child already
}


void Transform::UpdateTransformMatrix()
{
    CalculateTransformMatrixColumnMajor(m_localTransform, m_position, m_rotation);
	m_localTransform = XMMatrixMultiply(XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z), m_localTransform);

	if(m_parent != nullptr)
	{
		if(m_parent->GetIsDirty())
		{
			m_parent->UpdateTransformMatrix();
		}

		m_worldMatrix = XMMatrixMultiply(*m_parent->GetWorldTransform(), m_localTransform);

	}
	else
	{
		m_worldMatrix = m_localTransform;
	}
	

	//Update the world Postion
	m_worldPosition = XMVector4Transform( XMVectorSet(0.f,0.f,0.f,1.f), m_worldMatrix);

	//Update Rotation Matrix
	XMMATRIX rotationMatrix;
	CalculateRotationMatrix(rotationMatrix,  m_rotation);

	
	m_forward = XMVector3Normalize( XMVector4Transform( m_forwardRaw, rotationMatrix));


    m_dirty = false;
}

XMMATRIX* Transform::GetLocalTransform()
{
    if(m_dirty)
    {
        UpdateTransformMatrix();
    }

    return &m_localTransform;
}

XMMATRIX* Transform::GetWorldTransform()
{
    if(m_dirty)
    {
        UpdateTransformMatrix();
    }

    return &m_worldMatrix;
}

XMVECTOR Transform::GetWorldPosition()
{
	if(m_dirty)
    {
        UpdateTransformMatrix();
    }

	return m_worldPosition;
}


XMVECTOR Transform::GetForwardDirection()
{
	if(m_dirty)
	{
		UpdateTransformMatrix();
	}

	return m_forward;
}


/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> SERIALISATION <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/

JsonUtils::JsonElement* Transform::Serialise()
{
	JsonUtils::ArrayElement* array = new JsonUtils::ArrayElement();

    std::stringstream ss;
    ss << m_position.x << ' ' << m_position.y << ' ' << m_position.z;
	{
		const std::string& tmp = ss.str();
		char* chara = new char[tmp.length()+1];
		tmp.copy(chara, tmp.length());
		chara[tmp.length()] = '\0';
		array->elements.push_back(new JsonUtils::ValueElement("Position", chara));
		ss.str("");
	}

    ss << m_scale.x << ' ' << m_scale.y << ' ' << m_scale.z;
	{
		const std::string& tmp = ss.str();
		char* chara = new char[tmp.length() + 1];
		tmp.copy(chara, tmp.length());
		chara[tmp.length()] = '\0';
		array->elements.push_back(new JsonUtils::ValueElement("Scale", chara));
		ss.str("");
	}

	array->elements.push_back(new JsonUtils::ValueElement("Rotation", m_rotation.ToString()));


	ss << (m_parent != nullptr ? m_parent->GetGameObject()->GetID() : -1);
	{
		const std::string& tmp = ss.str();
		char* chara = new char[tmp.length() + 1];
		tmp.copy(chara, tmp.length());
		chara[tmp.length()] = '\0';
		array->elements.push_back(new JsonUtils::ValueElement("Parent", chara));
		ss.str("");
	}

    return array;
}

void Transform::Deserialise(JsonUtils::JsonElement* object)
{
	JsonUtils::ArrayElement* array = static_cast<JsonUtils::ArrayElement*>(object);

    JsonUtils::ValueElement* element = static_cast<JsonUtils::ValueElement*>(array->elements[0]);

    std::stringstream ss = std::stringstream(element->element);
    ss >> m_position.x;
    ss >> m_position.y;
    ss >> m_position.z;

	element = static_cast<JsonUtils::ValueElement*>(array->elements[1]);
    ss.str(element->element);
    ss >> m_position.x;
    ss >> m_position.y;
    ss >> m_position.z;

	element = static_cast<JsonUtils::ValueElement*>(array->elements[2]);
    m_rotation.Parse(element->element);
	element = static_cast<JsonUtils::ValueElement*>(array->elements[3]);
	m_parentID = StrUtils::stoi(element->element);
	if (m_parentID != -1)
	{
		SetParent(SceneManager::GetInstance().GetObjectInScene(m_parentID)->GetTransform());
		DBOUT("\tParent ID: " << m_parentID);
		DBOUT("\tParent Name: " << m_parent->GetGameObject()->GetName());

	}
}