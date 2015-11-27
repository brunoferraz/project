#version 400

in vec4 in_Position;
out vec4 nColor;
out float depth;

uniform vec2 in_Viewport;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

float near = 0.1;
float far = 10000.0;

void main(void)
{
    vec4 proj =  viewMatrix * modelMatrix * in_Position;

// to normalize between 0 and 1;
    depth = -(proj.z - near) / (far - near);

    gl_Position = projectionMatrix * proj;
}
