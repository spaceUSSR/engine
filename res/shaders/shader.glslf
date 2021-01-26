#version 460 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 texCord;

uniform sampler2D texture1;
uniform sampler2D texture2;	
uniform float visibleStatus;
void main()
{
	FragColor = mix(texture(texture1, texCord), texture(texture2, vec2(texCord.x / 2.0, texCord.y / 2.0)), visibleStatus);
}
