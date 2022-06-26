#version 330 core
out vec4 FragColor;

in vec3 outLocalPos;
in vec3 outWorldPos;
in vec3 outNormal;
in vec2 outUV;
flat in int outColorID;

uniform sampler2D texDiffuse;
uniform sampler2D texSpecular;

uniform vec3 uCameraPos;
uniform vec3 uColor;

struct Attenuation {
    float constant;
    float linear;
    float quadratic;
};

struct PointLight {
    vec3 position;
    vec3 color;
    float ambient;
    Attenuation atten;
};

uniform PointLight pointLight;

// To Implement Directional light
// Action Points :
// 1. Instead Light Position use Light Direction
// 2. Don't need Attenuation 
// 3. Implement CalcDirectionalLight

struct SpotLight {
    vec3 position;
    vec3 direction;
    vec3 color;
    float ambient;
    float cutoffAngle;
    float outercutoffAngle;
    Attenuation atten;
};

uniform SpotLight spotLight;
/*
SpotLight spotLight = SpotLight(
    vec3(0.0f, 3.0f, 0.0f), vec3(0.0f, -1.0f, 0.0f), vec3(1.0f, .0f, 0.0f), 0.1f, 55.0f, 60.0f, Attenuation(1.0, 0.027, 0.0028)
);
*/

const vec3 colors[6] = vec3[](
    vec3(1.0f, 0.0f, 0.0f),
    vec3(0.0f, 1.0f, 0.0f),
    vec3(0.0f, 0.0f, 1.0f),
    vec3(1.0f, 1.0f, 0.0f),
    vec3(0.0f, 1.0f, 1.0f),
    vec3(1.0f, 0.0f, 1.0f)
);

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform Material material;

uniform vec3 uTime;

/*
 Material material = Material(
    vec3(1.0f, 0.0f, 0.0f), vec3(0.5f, 0.0f, 0.0f), vec3(0.20f, 0.20, 0.20f), 1.0f
 );*/

float CalcAttenuation(vec3 lightPos, Attenuation atten, vec3 pos)
{
    float dist = distance(lightPos, pos);
    return 1.0f / (atten.constant + atten.linear * dist + atten.quadratic * dist * dist);
}

void CalcPointLight(in PointLight pointLight, in vec3 pos, inout vec3 ambientColor, inout vec3 diffuseColor, inout vec3 specularColor)
{
    float fAttenuation = CalcAttenuation(pointLight.position, pointLight.atten, outWorldPos);

    vec3 normal = normalize(outNormal);
    vec3 lightDirection = normalize(pointLight.position - outWorldPos);
    float diffuse = max(dot(lightDirection, normal), 0.0);

    vec3 cameraDirection = normalize(uCameraPos - outWorldPos);
    vec3 lightReflect = reflect(-lightDirection, normal);
    float specular = pow(max(dot(cameraDirection, lightReflect), 0.0), material.shininess);

    ambientColor += pointLight.color * pointLight.ambient * fAttenuation;
    diffuseColor += pointLight.color * diffuse * fAttenuation;
    specularColor += pointLight.color * specular * material.specular * fAttenuation;
}

void CalcSpotLight(in SpotLight spotLight,in vec3 pos,inout vec3 ambientColor, inout vec3 diffuseColor,inout vec3 specularColor)
{
    vec3 spotDirection = normalize(spotLight.direction);
    vec3 lightDirection = normalize(spotLight.position - pos);
    float theta = acos(dot(-lightDirection, spotDirection))*180.0f/3.14f;
    if(theta > spotLight.outercutoffAngle)
        return;

    float fDelta = spotLight.outercutoffAngle - spotLight.cutoffAngle;

    // 45.0f , 60.0f
    // theta = 30
    // (30 - 45)/15.0f = 1

    float fIntesitity = 1.0 - clamp((theta - spotLight.cutoffAngle)/fDelta, 0.0, 1.0);
    float fAttenuation = CalcAttenuation(spotLight.position, spotLight.atten, outWorldPos);

    vec3 normal = normalize(outNormal);
    float diffuse = max(dot(lightDirection, normal), 0.0);

    vec3 cameraDirection = normalize(uCameraPos - pos);
    vec3 lightReflect = reflect(-lightDirection, normal);
    float specular = pow(max(dot(cameraDirection, lightReflect), 0.0), material.shininess);

    ambientColor += spotLight.color * spotLight.ambient * fIntesitity * fAttenuation;
    diffuseColor += spotLight.color * diffuse * fIntesitity * fAttenuation;
    specularColor += spotLight.color * specular * material.specular * fIntesitity * fAttenuation;
}

void main()
{
    vec4 colorDiffuseMap = texture(texDiffuse, outUV);
    vec4 colorSpecularMap = texture(texSpecular, outUV);

    vec3 ambientColor = vec3(0.0);
    vec3 diffuseColor = vec3(0.0);
    vec3 specularColor = vec3(0.0);

    CalcPointLight(pointLight, outWorldPos, ambientColor, diffuseColor, specularColor);
    //CalcDirectionalLight(directionalLight, outWorldPos, ambientColor, diffuseColor, specularColor);
    CalcSpotLight(spotLight, outWorldPos, ambientColor, diffuseColor, specularColor);

    ambientColor *= colorDiffuseMap.rgb;
    diffuseColor *= colorDiffuseMap.rgb;
    specularColor *= colorSpecularMap.rgb;

    vec3 finalColor = ambientColor + diffuseColor + specularColor;

    FragColor = vec4(finalColor, colorDiffuseMap.a);
    //FragColor = vec4(finalColor*colors[outColorID], 1.0);
    //FragColor = vec4(finalColor, 1.0);
};