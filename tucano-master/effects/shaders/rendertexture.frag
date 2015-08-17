#version 130

uniform sampler2D imageTexture;
uniform ivec2 viewportSize;

out vec4 out_Color;

void main()
{
  vec2 texCoord = vec2(gl_FragCoord.xy/vec2(viewportSize.xy));
  vec3 result = texture(imageTexture, texCoord).rgb;
  gl_FragDepth = 0.0;
  out_Color = vec4(result, 1.0);
}
