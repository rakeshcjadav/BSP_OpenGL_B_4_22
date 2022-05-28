#include"Material.h"
#include"Program.h"
#include"Texture.h"
#include"GLM.h"

CMaterial* CMaterial::CreateMaterial(const char* strName)
{
    CMaterial* pMat = new CMaterial(strName);
    if (!pMat->LoadPrivate(strName))
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

void CMaterial::AddTexture(CTexture* pTexture)
{
    m_aTextures.push_back(pTexture);
}

void CMaterial::RemoveTexture(CTexture* pTexture)
{
    m_aTextures.remove(pTexture);
}


extern glm::vec3 g_vCameraPos;
extern glm::vec3 g_vCameraFront;
extern glm::vec3 g_vCameraUp;


void CMaterial::Use()
{
    m_pProgram->Use();

    glm::mat4 matWorld = glm::mat4(1.0f);
    matWorld = glm::translate(matWorld, glm::vec3(0.0f, 0.0f, 0.0f));
    //matWorld = glm::rotate(matWorld, scale*5.0f, glm::vec3(1.0f, 1.0f, 0.0f));
    //matWorld = glm::scale(matWorld, glm::vec3(scale*2.0, scale*2.0f, 1.0f));

    glm::mat4 matProjection;
    matProjection = glm::perspective(glm::radians(60.0f), 1280 / (720 * 1.0f), 0.1f, 100.0f);

    glm::mat4 matWorldProjection = matProjection * matWorld;

    glm::mat4 matView = glm::mat4(1.0f);
    matView = glm::lookAt(g_vCameraPos, g_vCameraPos + g_vCameraFront, g_vCameraUp);

    m_pProgram->SetUniformMatrix("uCombinedTransform", matWorldProjection);
    m_pProgram->SetUniformMatrix("uWorldMatrix", matWorld);
    m_pProgram->SetUniformMatrix("uViewMatrix", matView);
    m_pProgram->SetUniformMatrix("uProjectionMatrix", matProjection);

    m_pProgram->SetUniformFloat("uScale", 1.0f);

    m_pProgram->SetUniformColor("uColor", glm::vec3(0.0f, 0.0f, 1.0f));
    m_pProgram->SetUniformColor("uOffset", glm::vec3(0.0f, 0.0f, 0.0f));

    m_pProgram->SetUniformInt("texContainer", 0);
    m_pProgram->SetUniformInt("texMinion", 1);


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

bool CMaterial::LoadPrivate(const char* strName)
{
    return true;
}
