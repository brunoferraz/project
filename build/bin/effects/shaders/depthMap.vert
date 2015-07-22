#version 130

in vec4 in_Position;
in vec3 in_Normal;
in vec4 in_Color;
in vec2 in_TexCoords;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 lightViewMatrix;

out vec4 vert;
//out vec3 normal;
out vec4 color;
out float depth;



void main(void)
{
    mat4 modelViewMatrix = viewMatrix * modelMatrix;

    gl_Position = (projectionMatrix * modelViewMatrix) * in_Position;
//    gl_Position = (projectionMatrix *lightViewMatrix) * in_Position;
    vert = lightViewMatrix * in_Position;
    depth = vec4(lightViewMatrix * normalize(in_Position)).z;

    color = vec4 (depth, depth, depth, 1.0);
}
