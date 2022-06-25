#pragma once

#include"GLM.h"

struct SAttenuationDef
{
    float constant;
    float linear;
    float quadratic;
};

class CPointLight
{
public:
    static CPointLight* Create(glm::vec3 position, glm::vec3 color, float ambientstrength, SAttenuationDef& def);
    void Destroy();
    glm::vec3 GetPosition();
    glm::vec3 GetColor();
    float GetAmbientStrength();
    float GetAttenuationConstant();
    float GetAttenuationLinear();
    float GetAttenuationQuadratic();
protected:
    CPointLight();
    ~CPointLight();
    bool LoadPrivate(glm::vec3 position, glm::vec3 color, float ambientstrength, SAttenuationDef& def);
private:
    glm::vec3 m_vPosition;
    glm::vec3 m_vColor;
    float m_fAmbientStrength;
    SAttenuationDef m_AttenuationDef;
};