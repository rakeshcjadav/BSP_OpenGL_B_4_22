#include"MeshRenderer.h"
#include"MeshFilter.h"
#include"Material.h"
#include"Camera.h"
#include"Transform.h"
#include"PointLight.h"

CMeshRenderer* CMeshRenderer::Create()
{
    CMeshRenderer* pRenderer = new CMeshRenderer();
    if (!pRenderer->LoadPrivate())
    {
        pRenderer->Destroy();
        pRenderer = nullptr;
    }
    return pRenderer;
}

void CMeshRenderer::Destroy()
{
    delete this;
}

void CMeshRenderer::SetMeshFilter(CMeshFilter* pMeshFilter)
{
    m_pMeshFilter = pMeshFilter;
}

void CMeshRenderer::SetMaterial(CMaterial* pMaterial)
{
    m_pMaterial = pMaterial;
}

void CMeshRenderer::Render(CCamera* pCamera, CTransform* pTransform, CPointLight* pPointLight)
{
    m_pMaterial->Use(pCamera);
    m_pMaterial->SetUniformMatrix("uWorldMatrix", pTransform->GetTransformMatrix());
    if (pPointLight)
    {
        m_pMaterial->SetUniformColor("pointLight.position", pPointLight->GetPosition());
        m_pMaterial->SetUniformColor("pointLight.color", pPointLight->GetColor());
        m_pMaterial->SetUniformFloat("pointLight.ambient", pPointLight->GetAmbientStrength());

        m_pMaterial->SetUniformFloat("pointLight.atten.constant", pPointLight->GetAttenuationConstant());
        m_pMaterial->SetUniformFloat("pointLight.atten.linear", pPointLight->GetAttenuationLinear());
        m_pMaterial->SetUniformFloat("pointLight.atten.quadratic", pPointLight->GetAttenuationQuadratic());
    }
    m_pMeshFilter->Render();
}

CMeshRenderer::CMeshRenderer()
{

}

CMeshRenderer::~CMeshRenderer()
{

}

bool CMeshRenderer::LoadPrivate()
{
    return true;
}