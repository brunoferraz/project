#version 400

in vec4 in_Position;
out vec4 nColor;

uniform float adjustment;


void main(void)
{
    //nPos = vec4(inPos.xyz + vec3(0.001, 0.001,0), 1.0);
    vec4 norm = normalize(in_Position);
    nColor = norm;
}
