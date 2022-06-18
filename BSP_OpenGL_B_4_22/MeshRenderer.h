#pragma once

#include<list>
#include<string>

//Forward Declaration
class CMeshFilter;
class CMaterial;
class CCamera;
class CTransform;

class CMeshRenderer
{
public:
    static CMeshRenderer* Create();
    void Destroy();
    void SetMeshFilter(CMeshFilter* pMeshFilter);
    void SetMaterial(CMaterial* pMaterial);
    void Render(CCamera * pCamera, CTransform* pTransform);
private:
    CMeshRenderer();
    ~CMeshRenderer();
    bool LoadPrivate();
private:
    CMeshFilter* m_pMeshFilter;
    CMaterial* m_pMaterial;
};