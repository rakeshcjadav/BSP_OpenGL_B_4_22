#pragma once

#include<string>

// Forward 
class CMeshRenderer;

class CObject
{
public:
    static CObject* CreateObject(const char* strName);
    void Destroy();
    void SetMeshRenderer(CMeshRenderer* pMeshFilter);
    void Render();
protected:
    CObject(const char* strName);
    ~CObject();
    bool LoadPrivate(const char* strName);
private:
    CMeshRenderer* m_pMeshRenderer;
    std::string m_strName;
};