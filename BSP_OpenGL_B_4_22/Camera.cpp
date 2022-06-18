#include"Camera.h"

CCamera* CCamera:: CreateCamera(float fAspectRatio, float fFOV, float fNearPlane, float fFarPlane)
{
    CCamera* pCamera = new CCamera();
    if (!pCamera->LoadPrivate(fAspectRatio, fFOV, fNearPlane, fFarPlane))
    {
        pCamera->Destroy();
        pCamera = nullptr;
    }
    return pCamera;
}

void CCamera::Destroy()
{
    delete this;
}

void CCamera::SetPosition(glm::vec3 pos)
{
    m_vPosition = pos;
}

glm::vec3 CCamera::GetPosition()
{
    return m_vPosition;
}

void CCamera::SetDirection(glm::vec3 direction)
{
    m_vDirection = direction;
}

glm::vec3 CCamera::GetDirection()
{
    return m_vDirection;
}

void CCamera::MoveForward(float fSpeed)
{
    m_vPosition += m_vDirection * fSpeed;
}

void CCamera::MoveRight(float fSpeed)
{
    m_vPosition += glm::normalize(glm::cross(m_vDirection, m_vUp)) * fSpeed;
}

glm::mat4 CCamera::GetProjectionMatrix()
{
    return glm::perspective(glm::radians(m_fFOV), m_fAspectRatio, m_fNearPlane, m_fFarPlane);
}

glm::mat4 CCamera::GetViewMatrix()
{
    return glm::lookAt(m_vPosition, m_vPosition + m_vDirection, m_vUp);
}

CCamera::CCamera()
{

}

CCamera::~CCamera()
{

}

bool CCamera::LoadPrivate(float fAspectRatio, float fFOV, float fNearPlane, float fFarPlane)
{
    m_fAspectRatio = fAspectRatio;
    m_fFOV = fFOV;
    m_fNearPlane = fNearPlane;
    m_fFarPlane = fFarPlane;
    return true;
}