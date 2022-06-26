#include"Material.h"
#include"Program.h"
#include"Texture.h"
#include"Camera.h"
#include"GLFW/glfw3.h"

CMaterial* CMaterial::CreateMaterial(const char* strName, SMaterialProperties& material)
{
    CMaterial* pMat = new CMaterial(strName);
    if (!pMat->LoadPrivate(strName, material))
    {
        pMat->Destroy();
        pMat = nullptr;
    }
    return pMat;
}

void CMaterial::Destroy()
{
    delete this;
}

void CMaterial::SetProgram(CProgram* pProgram)
{
    m_pProgram = pProgram;
}

void CMaterial::SetUniformMatrix(const char* name, const glm::mat4& mat)
{
    m_pProgram->SetUniformMatrix(name, mat);
}

void CMaterial::SetUniformFloat(const char* name, float fValue)
{
    m_pProgram->SetUniformFloat(name, fValue);
}

void CMaterial::SetUniformColor(const char* name, const glm::vec3& color)
{
    m_pProgram->SetUniformColor(name, color);
}

void CMaterial::AddTexture(CTexture* pTexture)
{
    m_aTextures.push_back(pTexture);
}

void CMaterial::RemoveTexture(CTexture* pTexture)
{
    m_aTextures.remove(pTexture);
}

void CMaterial::Use(CCamera* pCamera)
{
    m_pProgram->Use();

    glm::mat4 matProjection = pCamera->GetProjectionMatrix();
    glm::mat4 matView = pCamera->GetViewMatrix();

    m_pProgram->SetUniformColor("uCameraPos", pCamera->GetPosition());
    m_pProgram->SetUniformMatrix("uViewMatrix", matView);
    m_pProgram->SetUniformMatrix("uProjectionMatrix", matProjection);

    float time = (float)glfwGetTime();
    float sinetime = sin(time);
    float fasttime = time*10;
    m_pProgram->SetUniformColor("uTime", glm::vec3(time, sinetime, fasttime));

    m_pProgram->SetUniformFloat("uScale", 1.0f);

    m_pProgram->SetUniformColor("uColor", glm::vec3(0.0f, 0.0f, 1.0f));
    m_pProgram->SetUniformColor("uOffset", glm::vec3(0.0f, 0.0f, 0.0f));

    m_pProgram->SetUniformInt("texDiffuse", 0);
    m_pProgram->SetUniformInt("texSpecular", 1);

    // Material properties
    m_pProgram->SetUniformColor("material.ambient", m_MaterialProperties.ambientColor);
    m_pProgram->SetUniformColor("material.diffuse", m_MaterialProperties.diffuseColor);
    m_pProgram->SetUniformColor("material.specular", m_MaterialProperties.specularColor);
    m_pProgram->SetUniformFloat("material.shininess", m_MaterialProperties.shininess);

    unsigned int index = 0;
    for (CTexture* pTexture : m_aTextures)
    {
        pTexture->Bind(index++);
    }
}

CMaterial::CMaterial(const char* strName)
{
    m_strName = strName;
}

CMaterial::~CMaterial()
{
    m_pProgram = nullptr;
    m_aTextures.clear();
}

bool CMaterial::LoadPrivate(const char* strName, SMaterialProperties& material)
{
    m_MaterialProperties = material;
    return true;
}
