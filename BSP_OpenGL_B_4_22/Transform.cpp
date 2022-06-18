#include"Transform.h"

CTransform* CTransform::CreateTransform(glm::vec3 pos, glm::vec3 rotation, glm::vec3 scale)
{
    CTransform* pTransform = new CTransform();
    if (!pTransform->LoadPrivate(pos, rotation, scale))
    {
        pTransform->Destroy();
        pTransform = nullptr;
    }
    return pTransform;
}

void CTransform::Destroy()
{
    delete this;
}

void CTransform::SetPosition(glm::vec3 pos)
{
    m_vPosition = pos;
    UpdateTransform();
}

glm::mat4 CTransform::GetTransformMatrix()
{
    return m_vTransform;
}

CTransform::CTransform()
{

}

CTransform::~CTransform()
{

}

bool CTransform::LoadPrivate(glm::vec3 pos, glm::vec3 rotation, glm::vec3 scale)
{
    m_vPosition = pos;
    m_vRotation = rotation;
    m_vScale = scale;

    UpdateTransform();
    return true;
}

void CTransform::UpdateTransform()
{
    // Order : Scale -> Rotate -> Translate
    m_vTransform =
        glm::translate(glm::identity<glm::mat4>(), m_vPosition)
        * glm::toMat4(glm::quat(glm::radians(m_vRotation)))
        * glm::scale(glm::identity<glm::mat4>(), m_vScale);
}