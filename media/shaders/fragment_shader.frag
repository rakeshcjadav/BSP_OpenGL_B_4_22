#version 330 core
out vec4 FragColor;

in vec3 outLocalPos;
in vec3 outWorldPos;
in vec3 outNormal;
in vec2 outUV;
flat in int outColorID;

uniform sampler2D texContainer;
uniform sampler2D texMinion;

uniform vec3 uCameraPos;
uniform vec3 uColor;

const vec3 colors[6] = vec3[](
    vec3(1.0f, 0.0f, 0.0f),
    vec3(0.0f, 1.0f, 0.0f),
    vec3(0.0f, 0.0f, 1.0f),
    vec3(1.0f, 1.0f, 0.0f),
    vec3(0.0f, 1.0f, 1.0f),
    vec3(1.0f, 0.0f, 1.0f)
);

vec3 lightPos = vec3(0.0f, 3.0f, 3.0f);
vec3 lightColor = vec3(0.8f, 0.8f, 1.0f);
float AmbientStrength = 0.1f;

void main()
{
    vec4 colorContainer = texture(texContainer, outUV);
    vec4 colorMinion = texture(texMinion, outUV);
    vec3 color = colorMinion.rgb * colorMinion.a + colorContainer.rgb * (1 - colorMinion.a);

    vec3 ambientColor = lightColor * AmbientStrength;

    vec3 normal = normalize(outNormal);
    vec3 lightDirection = normalize(lightPos - outWorldPos);
    float diffuse = max(dot(lightDirection, normal), 0);
    vec3 diffuseColor = lightColor * diffuse;

    vec3 cameraDirection = normalize(uCameraPos - outWorldPos);
    vec3 lightReflect = reflect(-lightDirection, normal);

    float specular = pow(max(dot(cameraDirection, lightReflect), 0.0), 32);

    vec3 specularColor = lightColor * specular;

     vec3 finalLight = ambientColor + diffuseColor + specularColor;

    FragColor = vec4(finalLight*color, colorContainer.a);
    //FragColor = vec4(colors[outColorID], 1.0);
};