#version 130

in vec4 color;
in vec3 normal;
in vec4 vert;

in vec2 texCoords;
in float depth;

//out vec4 out_Color;

uniform mat4 lightViewMatrix;
uniform sampler2D imageTexture;

void main(void)
{
    vec2 texCoord = vec2(gl_FragCoord.xy/vec2(381,281));
    vec3 result = texture2D(imageTexture, texCoord).rgb;
    gl_FragColor = vec4(result,1.0);
}
