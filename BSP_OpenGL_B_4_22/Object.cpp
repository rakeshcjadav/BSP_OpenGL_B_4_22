#include"Object.h"
#include"MeshRenderer.h"
#include"Camera.h"
#include"Transform.h"

CObject* CObject::CreateObject(const char* strName)
{
    CObject* pObj = new CObject(strName);
    if (!pObj->LoadPrivate(strName))
    {
        pObj->Destroy();
        pObj = nullptr;
    }
    return pObj;
}

void CObject::Destroy()
{
    delete this;
}

void CObject::SetMeshRenderer(CMeshRenderer* pMeshRenderer)
{
    if (m_pMeshRenderer)
        m_pMeshRenderer->Destroy();
    m_pMeshRenderer = pMeshRenderer;
}

void CObject::SetTransform(CTransform* pTransform)
{
    if (m_pTransform)
        m_pTransform->Destroy();
    m_pTransform = pTransform;
}

CTransform* CObject::GetTransform()
{
    return m_pTransform;
}

void CObject::Render(CCamera* pCamera)
{
    m_pMeshRenderer->Render(pCamera, m_pTransform);
}

CObject::CObject(const char* strName)
{
    m_strName = strName;
}

CObject::~CObject()
{
    m_pMeshRenderer->Destroy();
    m_pMeshRenderer = nullptr;
}

bool CObject::LoadPrivate(const char* strName)
{
    m_pTransform = CTransform::CreateTransform(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f));
    return !!m_pTransform;
}