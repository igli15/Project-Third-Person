//DIFFUSE COLOR VERTEX SHADER

#version 330 // for glsl version (12 is for older versions , say opengl 2.1

in vec3 vertex;
in vec3 normal;
in vec2 uv;

uniform	mat4 	projectionMatrix;
uniform	mat4 	viewMatrix;
uniform	mat4 	modelMatrix;

out vec3 fragPos;
out vec3 fnormal;

void main( void )
{
    	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertex, 1.0);
		
		fnormal = mat3(transpose(inverse(viewMatrix * modelMatrix))) * normal;
		
		fragPos = vec3(viewMatrix * modelMatrix * vec4(vertex,1.0));

}
