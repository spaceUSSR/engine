#version 460 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 texCord;

uniform sampler2D texture1;
uniform sampler2D texture2;	

uniform vec3 lightColor;
void main()
{
	FragColor = vec4(lightColor, 1.0) * texture(texture1, texCord);
}
