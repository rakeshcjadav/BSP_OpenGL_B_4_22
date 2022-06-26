#pragma once

#include"LightDef.h"

class CSpotLight
{
public:
    static CSpotLight* Create(SPointLightDef& spotLightDef, SAttenuationDef& def);
    void Destroy();
    glm::vec3 GetPosition();
    glm::vec3 GetDirection();
    glm::vec3 GetColor();
    float GetAmbientStrength();
    float GetInnerCutoffAngle();
    float GetOuterCutoffAngle();
    float GetAttenuationConstant();
    float GetAttenuationLinear();
    float GetAttenuationQuadratic();
protected:
    CSpotLight();
    ~CSpotLight();
    bool LoadPrivate(SPointLightDef& spotLightDef, SAttenuationDef& def);
private:
    SPointLightDef m_SpotLightDef;
    SAttenuationDef m_AttenuationDef;
};