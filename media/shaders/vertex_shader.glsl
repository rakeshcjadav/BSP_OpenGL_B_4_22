#version 330 core
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTexCoord; // UV 
layout(location = 2) in int colorID;

uniform float uScale;
uniform vec3 uOffset;

out vec2 outUV;
flat out int outColorID;

uniform mat4 uCombinedTransform;
uniform mat4 uWorldMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uProjectionMatrix;

void main()
{
    vec4 vertexPos = uProjectionMatrix * uViewMatrix * uWorldMatrix * vec4(aPosition, 1.0);
    gl_Position = vertexPos;
    //gl_Position = vec4(aPosition*vec3(uScale) + uOffset, 1.0);
    outUV = aTexCoord;
    outColorID = colorID;
};