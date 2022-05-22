#version 330 core
out vec4 FragColor;

in vec2 outUV;
flat in int outColorID;

uniform sampler2D texContainer;
uniform sampler2D texMinion;

uniform vec3 uColor;

const vec3 colors[6] = vec3[](
    vec3(1.0f, 0.0f, 0.0f),
    vec3(0.0f, 1.0f, 0.0f),
    vec3(0.0f, 0.0f, 1.0f),
    vec3(1.0f, 1.0f, 0.0f),
    vec3(0.0f, 1.0f, 1.0f),
    vec3(1.0f, 0.0f, 1.0f)
);

void main()
{
    vec4 colorContainer = texture(texContainer, outUV);
    vec4 colorMinion = texture(texMinion, outUV);
    vec3 color = colorMinion.rgb * colorMinion.a + colorContainer.rgb * (1 - colorMinion.a);
    FragColor = vec4(color.rgb, colorContainer.a);
    //FragColor = vec4(colors[outColorID], 1.0);
};