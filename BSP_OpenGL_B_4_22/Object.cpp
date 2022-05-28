#include"Object.h"
#include"MeshRenderer.h"

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
    m_pMeshRenderer = pMeshRenderer;
}

void CObject::Render()
{
    m_pMeshRenderer->Render();
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
    return true;
}