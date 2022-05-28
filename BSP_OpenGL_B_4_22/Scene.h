#pragma once

#include<list>
#include<string>

//Forward Declaration
class CObject;
class CCamera;

class CScene
{
public:
    static CScene* CreateScene(const char* strName);
    void Destroy();
    void AddObject(CObject* pMeshFilter);
    void RemoveObject(CObject* pMeshFilter);
    void SetCamera(CCamera* pCamera);
    void Render(int x, int y, int width, int height, float fValue);
private:
    CScene(const char* strName);
    ~CScene();
    bool LoadPrivate(const char* strName);
private:
    std::list<CObject*> m_aObjects;
    CCamera* m_pCamera;
    std::string m_strName;
};