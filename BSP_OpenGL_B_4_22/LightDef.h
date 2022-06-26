#pragma once

#include"GLM.h"

struct SPointLightDef
{
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 color;
    float ambientstrength;
    float innterCutoffAngle;
    float outerCutoffAngle;
};

struct SAttenuationDef
{
    float constant;
    float linear;
    float quadratic;
};