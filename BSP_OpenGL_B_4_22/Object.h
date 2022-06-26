#pragma once

#include<string>

// Forward 
class CMeshRenderer;
class CCamera;
class CTransform;
class CPointLight;
class CSpotLight;

class CObject
{
public:
    static CObject* CreateObject(const char* strName);
    void Destroy();
    void SetMeshRenderer(CMeshRenderer* pMeshFilter);
    void SetTransform(CTransform* pTransform);
    CTransform* GetTransform();
    void Render(CCamera* pCamera, CPointLight* pPointLight, CSpotLight* pSpotLight);
protected:
    CObject(const char* strName);
    ~CObject();
    bool LoadPrivate(const char* strName);
private:
    CTransform* m_pTransform;
    CMeshRenderer* m_pMeshRenderer;
    std::string m_strName;
};