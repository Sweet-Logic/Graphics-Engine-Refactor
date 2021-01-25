#ifndef _CAMERA_COMPONENT_H_
#define _CAMERA_COMPONENT_H_
#include "../Component.h"

#include <DirectXMath.h>

class Transform;

class CameraComponent : public Component
{
    public:
    enum CameraMode
    {
        E_ORTHOGONAL,
        E_PERSPECTIVE
    };
    private:

    Transform* m_gameObjectTransform;
	DirectX::XMMATRIX m_viewMatrix;
    DirectX::XMVECTOR m_upVector;

    CameraMode m_cameraMode;

    float m_width = 0; 
    float m_height = 0;
    float m_nearZ = 0;
    float m_farZ = 0;

    void CalculateViewMatrix();

    public:
        virtual char* GetName() override {return "CameraComponent";}
        void SetCameraMode(CameraMode mode) {m_cameraMode = mode;}
        CameraMode GetCameraMode() {return m_cameraMode;}

    DirectX::XMMATRIX GetViewMatrix() {return m_viewMatrix;}


    virtual void Start() override;
    virtual void Update() override;
    virtual void PostUpdate() override;

	virtual JsonUtils::JsonElement* Serialise() override;
    virtual void Deserialise(JsonUtils::JsonElement* object) override;
};

#endif //!_CAMERA_COMPONENT_H_