#version 330

in vec4 vCol;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 color;

struct Light
{
	vec3 color;
	float ambientIntensity;
	float diffuseIntensity;
};

struct DirectionalLight 
{
	Light base;
	vec3 direction;
};

struct PointLight 
{
	Light base;
	vec3 position;
	vec3 attenuationVars;
};

struct Material
{
	float specularIntensity;
	float shininess;
};

uniform sampler2D theTexture;
uniform DirectionalLight directionalLight;
uniform Material material;

uniform vec3 eyePosition;

void main()
{
	vec4 ambientColor = vec4(directionalLight.base.color, 1.0) * directionalLight.base.ambientIntensity;

	float diffuseFactor = max(dot(normalize(Normal), normalize(directionalLight.direction)), 0.0f);
	vec4 diffuseColor = vec4(directionalLight.base.color, 1.0f) * directionalLight.base.diffuseIntensity * diffuseFactor;
	
	vec4 specularColor = vec4(0, 0, 0, 0);
	
	if(diffuseFactor > 0.0)
	{
		vec3 fragToEye = normalize(eyePosition - FragPos);
		vec3 reflectedVertex = normalize(reflect(directionalLight.direction, normalize(Normal)));
		
		float specularFactor = dot(fragToEye, reflectedVertex);
		if(specularFactor > 0.0f)
		{
			specularFactor = pow(specularFactor, material.shininess);
			specularColor  = vec4(directionalLight.base.color * material.specularIntensity * specularFactor, 1.0);
		}
	}
	
	color = texture(theTexture, TexCoord) * (ambientColor + diffuseColor + specularColor);
}