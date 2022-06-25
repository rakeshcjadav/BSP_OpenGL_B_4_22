#include"PointLight.h"

CPointLight* CPointLight::Create(glm::vec3 position, glm::vec3 color, float ambientstrength, SAttenuationDef& def)
{
    CPointLight* pLight = new CPointLight();
    if (!pLight->LoadPrivate(position, color, ambientstrength, def))
    {
        pLight->Destroy();
        pLight = nullptr;
    }
    return pLight;
}

void CPointLight::Destroy()
{
    delete this;
}

glm::vec3 CPointLight::GetPosition()
{
    return m_vPosition;
}

glm::vec3 CPointLight::GetColor()
{
    return m_vColor;
}

float CPointLight::GetAmbientStrength()
{
    return m_fAmbientStrength;
}

float CPointLight::GetAttenuationConstant()
{
    return m_AttenuationDef.constant;
}

float CPointLight::GetAttenuationLinear()
{
    return m_AttenuationDef.linear;
}

float CPointLight::GetAttenuationQuadratic()
{
    return m_AttenuationDef.quadratic;
}

CPointLight::CPointLight()
{

}

CPointLight::~CPointLight()
{

}

bool CPointLight::LoadPrivate(glm::vec3 position, glm::vec3 color, float ambientstrength, SAttenuationDef& def)
{
    m_vPosition = position;
    m_vColor = color;
    m_fAmbientStrength = ambientstrength;
    m_AttenuationDef = def;
    return true;
}