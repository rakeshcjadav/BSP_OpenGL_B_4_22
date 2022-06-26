#include"Scene.h"
#include"Camera.h"
#include"Object.h"
#include"glad/glad.h"
#include"PointLight.h"
#include"SpotLight.h"

CScene* CScene::CreateScene(const char* strName)
{
    CScene* pScene = new CScene(strName);
    if (!pScene->LoadPrivate(strName))
    {
        pScene->Destroy();
        pScene = nullptr;
    }
    return pScene;
}

void CScene::Destroy()
{
    delete this;
}

void CScene::AddObject(CObject* pObject, CTransform* pTransform)
{
    pObject->SetTransform(pTransform);
    m_aObjects.push_back(pObject);
}

void CScene::RemoveObject(CObject* pObject)
{
    m_aObjects.remove(pObject);
}

void CScene::SetPointLight(CPointLight* pPointLight)
{
    if(m_pPointLight)
        m_pPointLight->Destroy();
    m_pPointLight = pPointLight;
}

void CScene::SetSpotLight(CSpotLight* pSpotLight)
{
    if (m_pSpotLight)
        m_pSpotLight->Destroy();
    m_pSpotLight = pSpotLight;
}

void CScene::SetCamera(CCamera* pCamera)
{
    if (m_pCamera)
        m_pCamera->Destroy();
    m_pCamera = pCamera;
}

void CScene::Render(int x, int y, int width, int height, float fValue)
{
    glViewport(x, y, width, height);
    for (CObject* pObject : m_aObjects)
    {
        pObject->Render(m_pCamera, m_pPointLight, m_pSpotLight);
    }
}

CScene::CScene(const char* strName)
{
    m_pCamera = nullptr;
    m_pPointLight = nullptr;
}

CScene::~CScene()
{
    m_aObjects.clear();
    m_pCamera = nullptr;
}

bool CScene::LoadPrivate(const char* strName)
{
    m_strName = strName;
    return true;
}