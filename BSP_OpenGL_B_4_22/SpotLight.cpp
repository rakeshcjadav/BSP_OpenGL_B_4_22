#include"SpotLight.h"

CSpotLight* CSpotLight::Create(SPointLightDef& spotLightDef, SAttenuationDef& def)
{
    CSpotLight* pLight = new CSpotLight();
    if (!pLight->LoadPrivate(spotLightDef, def))
    {
        pLight->Destroy();
        pLight = nullptr;
    }
    return pLight;
}

void CSpotLight::Destroy()
{
    delete this;
}

glm::vec3 CSpotLight::GetPosition()
{
    return m_SpotLightDef.position;
}

glm::vec3 CSpotLight::GetDirection()
{
    return m_SpotLightDef.direction;
}

glm::vec3 CSpotLight::GetColor()
{
    return m_SpotLightDef.color;
}

float CSpotLight::GetAmbientStrength()
{
    return m_SpotLightDef.ambientstrength;
}

float CSpotLight::GetInnerCutoffAngle()
{
    return m_SpotLightDef.innterCutoffAngle;
}

float CSpotLight::GetOuterCutoffAngle()
{
    return m_SpotLightDef.outerCutoffAngle;
}

float CSpotLight::GetAttenuationConstant()
{
    return m_AttenuationDef.constant;
}

float CSpotLight::GetAttenuationLinear()
{
    return m_AttenuationDef.linear;
}

float CSpotLight::GetAttenuationQuadratic()
{
    return m_AttenuationDef.quadratic;
}

CSpotLight::CSpotLight()
{

}

CSpotLight::~CSpotLight()
{

}

bool CSpotLight::LoadPrivate(SPointLightDef& spotLightDef, SAttenuationDef& def)
{
    m_SpotLightDef = spotLightDef;
    m_AttenuationDef = def;
    return true;
}