#version 150

in vec4 color;
in vec3 normal;
in vec4 vert;

in vec2 texCoords;
in float depth;

out vec4 out_Color;

uniform mat4 lightViewMatrix;

void main(void)
{
    out_Color = vec4(depth, depth, depth, 1.0);
}
