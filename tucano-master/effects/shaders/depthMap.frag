#version 130

in vec4 vert;
in vec3 normal;
in vec4 color;

out vec4 out_Coords;
out vec4 out_Normal;
out vec4 out_Color;


void main(void)
{
//    out_Color = color;
    out_Coords = vec4 (vert.xyz, 1.0);
    out_Normal = vec4 (normal.xyz, 1.0);
    out_Color = color.rgba;
}
