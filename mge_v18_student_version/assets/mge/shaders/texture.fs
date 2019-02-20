//DIFFUSE TEXTURE FRAGMENT SHADER
#version 330 // for glsl version (12 is for older versions , say opengl 2.1

uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;
uniform sampler2D emissionTexture;

uniform vec3 diffuseColor;
uniform float shineness;
uniform float emissionScale;

uniform float pointLightCount;
uniform float directionalLightCount;
uniform float spotLightCount;

struct PointLight
{
	vec3 lightColor;
	vec3 lightPos;
	float ambientContribution;
	float specularContribution;
	
	float constant;
	float linear;
	float quadratic;
};

uniform PointLight[20] pointLight;

struct DirectionalLight
{
	vec3 lightColor;
	vec3 direction;
	float ambientContribution;
	float specularContribution;
};

uniform DirectionalLight[20] directionalLight;

struct SpotLight
{
	vec3 lightColor;
	vec3 lightPos;
	vec3 direction;
	
	float cutoff;
	float outerCutoff;
	
	float ambientContribution;
	float specularContribution;
	
	float constant;
	float linear;
	float quadratic;
	
};

uniform SpotLight[20] spotLight;

in vec3 fragPos;
in vec3 fnormal;
in vec2 texCoord;

out vec4 fragment_color;

vec3 CalculateDirectionalLight(DirectionalLight dirLight,vec3 normal);
vec3 CalculatePointLight(PointLight pointLight, vec3 normal,vec3 fragPos);
vec3 CalculateSpotLight(SpotLight spotLight,vec3 normal,vec3 fragPos);

void main( void ) 
{
	vec3 outputColor = vec3(0,0,0);
	vec3 n = normalize(fnormal);
	
for(int i =0 ; i<directionalLightCount;i++)
{
	 outputColor += CalculateDirectionalLight(directionalLight[i],n);
}

for(int i =0 ; i<pointLightCount;i++)
{
	 outputColor += CalculatePointLight(pointLight[i],n,fragPos);

}

for(int i =0 ; i<spotLightCount;i++)
{	
	 outputColor += CalculateSpotLight(spotLight[i],n,fragPos);
}

	float gamma = 2.2;
    
	outputColor.rgb = pow(outputColor.rgb, vec3(1.0/gamma));
	
	fragment_color = vec4 (outputColor,1);
}

vec3 CalculatePointLight(PointLight pointLight,vec3 normal,vec3 fragPos)
{
	vec3 ambient = pointLight.ambientContribution * pointLight.lightColor * vec3(texture(diffuseTexture,texCoord));
	
	vec3 lightDir = normalize(pointLight.lightPos - fragPos);
	
	float diff = max(dot(normal,lightDir),0);
	vec3 diffuse = diff * pointLight.lightColor * vec3(texture(diffuseTexture,texCoord));
	
	float distance = length(pointLight.lightPos - fragPos);
	
	float attenuation = 1.0/(pointLight.constant + pointLight.linear * distance + pointLight.quadratic * (distance * distance));
	
	vec3 viewDir = normalize(-fragPos);
	vec3 reflectDir = reflect(-lightDir,normal);
	vec3 halfwayDir = normalize(lightDir + viewDir);
	//float spec = pow(max(dot(viewDir,reflectDir),0),shineness);
	float spec = pow(max(dot(normal,halfwayDir),0),shineness);
	
	vec3 specular = spec * pointLight.specularContribution * pointLight.lightColor * vec3(texture(specularTexture,texCoord));
	
	if(pointLight.constant > 0)
	{
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;
	}
	
	vec3 emission = texture(emissionTexture, texCoord).rgb * emissionScale;
	 
	vec3 finalColor = (ambient + diffuse + specular + emission) * diffuseColor;
	return finalColor;
}

vec3 CalculateDirectionalLight(DirectionalLight dirLight,vec3 normal)
{
	vec3 ambient = dirLight.ambientContribution * dirLight.lightColor * vec3(texture(diffuseTexture,texCoord));
	
	vec3 lightDir = normalize(-dirLight.direction);
	
	float diff = max(dot(normal,lightDir),0);
	vec3 diffuse = diff * dirLight.lightColor * vec3(texture(diffuseTexture,texCoord));
	
	vec3 viewDir = normalize(-fragPos);
	vec3 reflectDir = reflect(-lightDir,normal);
	vec3 halfwayDir = normalize(lightDir + viewDir);
	//float spec = pow(max(dot(viewDir,reflectDir),0),shineness);
	float spec = pow(max(dot(normal,halfwayDir),0),shineness);
	
	vec3 specular = spec * dirLight.specularContribution * dirLight.lightColor * vec3(texture(specularTexture,texCoord));
	
	vec3 emission = texture(emissionTexture, texCoord).rgb * emissionScale;
	
	vec3 finalColor = (ambient + diffuse + specular + emission) * diffuseColor;
	return finalColor;
}

vec3 CalculateSpotLight(SpotLight spotLight,vec3 normal,vec3 fragPos)
{
	vec3 ambient = spotLight.ambientContribution * spotLight.lightColor * vec3(texture(diffuseTexture,texCoord));
	
	vec3 lightDir = normalize(spotLight.lightPos - fragPos);
	
	float diff = max(dot(normal,lightDir),0);
	vec3 diffuse = diff * spotLight.lightColor * vec3(texture(diffuseTexture,texCoord));
	
	float distance = length(spotLight.lightPos - fragPos) ;
	float attenuation = 1.0/(spotLight.constant + spotLight.linear * distance + spotLight.quadratic * (distance * distance));
	
	vec3 viewDir = normalize(-fragPos);
	vec3 reflectDir = reflect(-lightDir,normal);
	vec3 halfwayDir = normalize(lightDir + viewDir);
	//float spec = pow(max(dot(viewDir,reflectDir),0),shineness);
	float spec = pow(max(dot(normal,halfwayDir),0),shineness);
	
	vec3 specular = spec * spotLight.specularContribution * spotLight.lightColor * vec3(texture(specularTexture,texCoord));
	
	float dirAngle = dot(lightDir,normalize(-spotLight.direction));
	float delta = spotLight.cutoff - spotLight.outerCutoff;
	float spotIntensity = clamp((dirAngle-spotLight.outerCutoff)/delta,0.0,1.0);
	
	if(spotLight.constant > 0)
	{
	ambient *= attenuation * spotIntensity;
	diffuse *= attenuation * spotIntensity;
	specular *= attenuation * spotIntensity;
	}
	
	vec3 emission = texture(emissionTexture, texCoord).rgb * emissionScale;
	
	vec3 finalColor = (ambient + diffuse + specular + emission) * diffuseColor;
	return finalColor;
}