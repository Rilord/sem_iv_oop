#version 150

layout (location= 0) in vec3 inPos;
layout (location = 1) in vec3 inCol;

out vec3 vertCol;

uniform mat4 projectionMat;
uniform mat4 viewMat;
uniform mat4 modelMat;

void main()
{
    vertCol = inCol;
    vec4 modelPos = modelMat * vec4(inPos, 1.0);
    vec4 viewPos = viewMat * modelPos;
    gl_Position = projectionMat * viewPos;
}
