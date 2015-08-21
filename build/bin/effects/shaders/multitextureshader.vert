#version 130

in vec4 in_Position;
in vec3 in_Normal;
in vec2 in_TexCoords;
in vec4 in_Color;

out vec4 vert;


uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main(void)
{
    mat4 modelViewMatrix = modelMatrix * viewMatrix;

    vert = projectionMatrix * modelViewMatrix * in_Position;
    gl_Position = projectionMatrix * modelViewMatrix * in_Position;


    //use viewport size to get texture position.
}

