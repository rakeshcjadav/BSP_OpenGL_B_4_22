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

/*
 Material material = Material(
    vec3(1.0f, 0.0f, 0.0f), vec3(0.5f, 0.0f, 0.0f), vec3(0.20f, 0.20, 0.20f), 1.0f
 );*/

float CalcAttenuation(PointLight light, vec3 pos)
{
    float dist = distance(light.position, pos);
    return 1.0f / (light.atten.constant + light.atten.linear * dist + light.atten.quadratic * dist * dist);
}


void main()
{
    vec4 colorDiffuseMap = texture(texDiffuse, outUV);
    vec4 colorSpecularMap = texture(texSpecular, outUV);
    vec3 color = colorDiffuseMap.rgb;

    float fAttenuation = CalcAttenuation(pointLight, outWorldPos);

    vec3 ambientColor = pointLight.color * pointLight.ambient * colorDiffuseMap.rgb;

    vec3 normal = normalize(outNormal);
    vec3 lightDirection = normalize(pointLight.position - outWorldPos);
    float diffuse = max(dot(lightDirection, normal), 0.0);
    vec3 diffuseColor = pointLight.color * diffuse * colorDiffuseMap.rgb;

    vec3 cameraDirection = normalize(uCameraPos - outWorldPos);
    vec3 lightReflect = reflect(-lightDirection, normal);

    float specular = pow(max(dot(cameraDirection, lightReflect), 0.0), material.shininess);

    vec3 specularColor = pointLight.color * specular * colorSpecularMap.rgb * material.specular;

    vec3 finalColor = ambientColor + diffuseColor + specularColor;

    FragColor = vec4(finalColor*fAttenuation, colorDiffuseMap.a);
    //FragColor = vec4(finalColor*colors[outColorID], 1.0);
    //FragColor = vec4(finalColor, 1.0);
};