#version 400

in vec4 in_Position;
out vec4 nColor;

uniform vec2 in_Viewport;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform sampler2D depthMapTexture;
uniform sampler2D imageTexture;
float near = 0.1;
float far = 10000.0;

void main(void)
{
    vec4 proj = viewMatrix * modelMatrix * in_Position;
    // to normalize between 0 and 1;
    float depth  = -(proj.z - near) / (far - near);

    // divide by W and normalize between 0 and 1;
    vec4 texcoord = projectionMatrix * proj;
    texcoord /= texcoord.w;
    texcoord.xy = (texcoord.xy * 0.5) + 0.5;

    vec4 color = vec4(1.0, 1.0, 1.0, 1.0);
    if(texture2D(depthMapTexture, texcoord.xy).z > depth - 0.0005){
//        color = vec4(1.0);
        color  = texture2D(imageTexture, texcoord.xy);
    }
    nColor = color;
}
