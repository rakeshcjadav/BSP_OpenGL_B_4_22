#pragma once

#include<list>
#include<string>
#include"GLM.h"

class CProgram;
class CTexture;
class CCamera;
struct SMaterialProperties
{
    glm::vec3 ambientColor;
    glm::vec3 diffuseColor;
    glm::vec3 specularColor;
    float shininess;
};

class CMaterial
{
public:
    static CMaterial* CreateMaterial(const char* strName, SMaterialProperties & material);
    void Destroy();
    void SetProgram(CProgram* pProgram);
    void SetUniformMatrix(const char* name, const glm::mat4& mat);
    void SetUniformFloat(const char* name, float fValue);
    void SetUniformColor(const char* name, const glm::vec3& color);
    void AddTexture(CTexture* pTexture);
    void RemoveTexture(CTexture* pTexture);
    void Use(CCamera* pCamera);
private:
    CMaterial(const char* strName);
    ~CMaterial();
    bool LoadPrivate(const char* strName, SMaterialProperties& material);
private:
    std::string m_strName;
    SMaterialProperties m_MaterialProperties;
    CProgram* m_pProgram;
    std::list<CTexture*> m_aTextures;
};