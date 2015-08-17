#version 130

in vec4 in_Position;

void main()
{
  vec4 vert = in_Position;
  gl_Position = vert;
}
