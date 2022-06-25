#version 330 core
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord; // UV 
layout(location = 3) in int colorID;

uniform float uScale;
uniform vec3 uOffset;

out vec3 outLocalPos;
out vec3 outWorldPos;
out vec3 outNormal;
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
    outLocalPos = aPosition;
    outWorldPos = vec3(uWorldMatrix * vec4(aPosition, 1.0));
    //gl_Position = vec4(aPosition*vec3(uScale) + uOffset, 1.0);
    mat3 normalMat = transpose(inverse(mat3(uWorldMatrix))); // Remove translation => Transpose => Inverse
    outNormal = normalMat * aNormal;
    outUV = aTexCoord;
    outColorID = colorID;
};