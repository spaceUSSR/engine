	#version 460 core

out vec4 FragColor;
in vec2 texCord;
in vec3 Normal;
in vec3 fragPos;

struct Light {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};


struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	sampler2D lines;
	float shininess;
};

uniform vec3 viewPos;
uniform Material material;
uniform Light light;


void main()
{
	vec3 normal = normalize(Normal);
	vec3 boxTexture = texture(material.diffuse, texCord).rgb;
	vec3 lightDirection = normalize(light.position - fragPos);

	vec3 viewDirection = normalize(viewPos - fragPos);
	vec3 reflectDirection = reflect(-lightDirection, normal);

	float diff = max(dot(lightDirection, normal), 0.0);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);

	vec3 ambient = light.ambient		* texture(material.diffuse, texCord).rgb;
	vec3 diffuse = light.diffuse		* diff * texture(material.diffuse, texCord).rgb;
	vec3 specular = light.specular	* spec * texture(material.specular, texCord).rgb;

	vec3 result = ambient + diffuse + specular + texture(material.lines, texCord).rgb;
	FragColor = vec4(result, 1.0);

}
