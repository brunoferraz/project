#version 400

in vec4 in_Position;
in vec3 in_Normal;
in vec2 in_TexCoords;
in vec4 in_Color;

in vec2 in_coordText_0;
in vec2 in_coordText_1;
in vec2 in_coordText_2;
in vec2 in_coordText_3;
//in vec4 nColor;

out vec4 color;
out vec3 normal;
out vec4 vert;
out vec2 texCoords;

out float depth;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform vec4 default_color;

// if attribute in_Color exists or not
uniform bool has_color;

uniform sampler2D imageTexture_0;
uniform sampler2D imageTexture_1;
uniform sampler2D imageTexture_2;
uniform sampler2D imageTexture_3;
uniform sampler2D imageTexture_4;

void main(void)
{
	mat4 modelViewMatrix = viewMatrix * modelMatrix;

        mat4 normalMatrix = transpose(inverse(modelViewMatrix));
        normal = normalize(vec3(normalMatrix * vec4(in_Normal,0.0)).xyz);

	vert = modelViewMatrix * in_Position;

	depth = in_Position.z;

        texCoords = in_coordText_0;

	gl_Position = (projectionMatrix * modelViewMatrix) * in_Position;

        if(in_coordText_0.x < 0){
            color = texture2D(imageTexture_1, in_coordText_1);;
        }else{
            color = texture2D(imageTexture_0, in_coordText_0);
        }
}
