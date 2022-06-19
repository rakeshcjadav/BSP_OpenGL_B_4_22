#pragma once

#include"GLM.h"

class CTransform
{
public:
    static CTransform* CreateTransform(glm::vec3 pos, glm::vec3 rotation, glm::vec3 scale);
    void Destroy();
    void SetPosition(glm::vec3 pos);
    void SetRotation(glm::vec3 rotation);
    glm::mat4 GetTransformMatrix();
private:
    CTransform();
    ~CTransform();
    bool LoadPrivate(glm::vec3 pos, glm::vec3 rotation, glm::vec3 scale);
    void UpdateTransform();
private:
    glm::vec3 m_vPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 m_vRotation = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 m_vScale = glm::vec3(1.0f, 1.0f, 1.0f);

    glm::mat4 m_vTransform;
};
