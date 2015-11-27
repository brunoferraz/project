#version 130

in vec4 vert;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec2 in_viewPort;

out vec4 out_Color;

void main(void)
{
//    out_Color = vec4(vec2(gl_FragColor.xy/in_viewPort.xy), 0.0, 1.0);
    vec2 textCoord = gl_FragCoord.xy/in_viewPort.xy;
    out_Color = vec4(textCoord,0.0,1.0);
}

