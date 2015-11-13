#version 400

in vec4 in_Position;
in vec4 in_Color;

out vec4 color;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main(void)
{

        gl_Position = projectionMatrix * modelMatrix * viewMatrix * in_Position;
        color = in_Color;
}
