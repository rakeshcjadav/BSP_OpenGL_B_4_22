#include"MeshRenderer.h"
#include"MeshFilter.h"
#include"Material.h"
#include"Camera.h"

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

void CMeshRenderer::Render(CCamera* pCamera)
{
    m_pMaterial->Use(pCamera);
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