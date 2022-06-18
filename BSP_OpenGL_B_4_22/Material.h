#pragma once

#include<list>
#include<string>

class CProgram;
class CTexture;
class CCamera;

class CMaterial
{
public:
    static CMaterial* CreateMaterial(const char* strName);
    void Destroy();
    void SetProgram(CProgram* pProgram);
    void AddTexture(CTexture* pTexture);
    void RemoveTexture(CTexture* pTexture);
    void Use(CCamera* pCamera);
private:
    CMaterial(const char* strName);
    ~CMaterial();
    bool LoadPrivate(const char* strName);
private:
    std::string m_strName;
    CProgram* m_pProgram;
    std::list<CTexture*> m_aTextures;
};