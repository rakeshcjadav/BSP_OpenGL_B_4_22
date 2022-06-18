#pragma once

#include"GLM.h"

class CCamera
{
public:
    static CCamera* CreateCamera(float fAspectRatio, float fFOV, float fNearPlane, float fFarPlane);
    void Destroy();
    void SetPosition(glm::vec3 pos);
    glm::vec3 GetPosition();
    void SetDirection(glm::vec3 direction);
    glm::vec3 GetDirection();
    void MoveForward(float fSpeed);
    void MoveRight(float fSpeed);
    glm::mat4 GetProjectionMatrix();
    glm::mat4 GetViewMatrix();
private:
    CCamera();
    ~CCamera();
    bool LoadPrivate(float fAspectRatio, float fFOV, float fNearPlane, float fFarPlane);
private:
    glm::vec3 m_vPosition = glm::vec3(0.0f, 0.0f, 10.0f);
    glm::vec3 m_vDirection = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 m_vUp = glm::vec3(0.0f, 1.0f, 0.0f);

    float m_fFOV;
    float m_fAspectRatio;
    float m_fNearPlane;
    float m_fFarPlane;
};