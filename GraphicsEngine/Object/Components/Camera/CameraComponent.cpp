#include "CameraComponent.h"
#include "../Transform.h"

#include <DirectXMath.h>

using namespace DirectX;
void CameraComponent::CalculateViewMatrix()
{
    if(m_cameraMode == E_PERSPECTIVE)
    	m_viewMatrix = XMMatrixLookToLH(m_gameObjectTransform->GetWorldPosition(), m_gameObjectTransform->GetForwardDirection(), m_gameObjectTransform->GetUp());
    else
    // Implement Orthogonal Later
}

void CameraComponent::Start()
{
    m_gameObjectTransform = m_gameObject->GetTransform();
    m_upVector = XMVectorSet(0.f,1.f,0.f,0.f);
}

void CameraComponent::Update()
{
    if(m_gameObjectTransform->GetIsDirty())
    {
        CalculateViewMatrix();
    }
}

void CameraComponent::PostUpdate()
{

}
