#version 150

in vec3 vertCol;

out vec4 fragCol;

void main() 
{
    fragCol = vec4(vertCol, 1.0);
}
