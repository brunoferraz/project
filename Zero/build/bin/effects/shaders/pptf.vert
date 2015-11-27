#version 400

in vec4 inPos;
in vec4 vel;

out vec4 nPos;


void main(void)
{
    nPos = vec4(inPos.xyz + vec3(0.001, 0.001,0), 1.0);
}
