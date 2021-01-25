#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "Component.h"
#include "../../Utils/Maths/Vector3D.h"
#include "../../Utils/Maths/Quaternion.h"
#include "../../Utils/LinkedLists/LinkedLists.h"

#include <DirectXMath.h>


class Transform : public Component
{
    DirectX::XMFLOAT3 m_position;
    Quaternion m_rotation;
    DirectX::XMFLOAT3 m_scale;

    DirectX::XMVECTOR m_worldPosition;

    DirectX::XMVECTOR m_up;
    DirectX::XMVECTOR m_forward;
    static DirectX::XMVECTOR m_forwardRaw;

    LinkedList<Transform*> m_children;
    Transform* m_parent;
    int m_parentID = -1;

    bool m_dirty = true;

    DirectX::XMMATRIX m_localTransform;
    DirectX::XMMATRIX m_worldMatrix;


    public:

    void SetDirty();
    void UpdateTransformMatrix();

    virtual void Start() override;
    virtual void Update() override;
    virtual void PostUpdate() override;

    bool GetIsDirty() {return m_dirty;}

	virtual JsonUtils::JsonElement* Serialise();
    virtual void Deserialise(JsonUtils::JsonElement* object);


    DirectX::XMVECTOR GetForwardDirection();
    DirectX::XMVECTOR GetUp() {return m_up;};
    DirectX::XMVECTOR GetWorldPosition();
    DirectX::XMMATRIX* GetLocalTransform();
    DirectX::XMMATRIX* GetWorldTransform();

	void SetPosition(DirectX::XMFLOAT3) {};
	void SetScale(DirectX::XMFLOAT3) {};
	void SetRotation(Quaternion) {};

    void SetParent(Transform* parent);
    void SetChild(Transform* child);

    virtual char* GetName() {return "Transform";};

	LinkedList<Transform*> GetChildren() { return m_children; };

};

#endif //!_TRANSFORM_H_