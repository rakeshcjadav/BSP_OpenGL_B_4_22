#include"Scene.h"
#include"Camera.h"
#include"Object.h"
#include"glad/glad.h"

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

void CScene::AddObject(CObject* pObject)
{
    m_aObjects.push_back(pObject);
}

void CScene::RemoveObject(CObject* pObject)
{
    m_aObjects.remove(pObject);
}

void CScene::SetCamera(CCamera* pCamera)
{
    m_pCamera = pCamera;
}

void CScene::Render(int x, int y, int width, int height, float fValue)
{
    glViewport(x, y, width, height);
    for (CObject* pObject : m_aObjects)
    {
        pObject->Render();
    }
}

CScene::CScene(const char* strName)
{

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