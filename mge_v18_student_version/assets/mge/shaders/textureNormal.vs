//DIFFUSE TEXTURE VERTEX SHADER
#version 330 // for glsl version (12 is for older versions , say opengl 2.1

uniform	mat4 	projectionMatrix;
uniform	mat4 	viewMatrix;
uniform	mat4 	modelMatrix;

uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;
uniform sampler2D emissionTexture;

in vec3 vertex;
in vec3 normal;
in vec2 uv;

in vec3 tangent;
in vec3 bitangent;

out vec2 texCoord; //make sure the texture coord is interpolated
out vec3 fragPos;
out vec3 fnormal;


out mat3 TBN;

void main( void ){
    
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertex, 1.0);
	
	texCoord = uv;
	fnormal = mat3(transpose(inverse(viewMatrix * modelMatrix))) * normal;
		
	fragPos = vec3(viewMatrix * modelMatrix * vec4(vertex,1.0));
	
	vec3 T = normalize(vec3(modelMatrix * vec4(tangent, 0.0)));
	vec3 N = normalize(vec3(modelMatrix * vec4(normal, 0.0)));

	T = normalize(T - dot(T, N) * N);

	vec3 B = cross(N, T);
	
	TBN = mat3(T,B,N);
	
	
}
