#version 330

layout(location = 0) in vec3 vertexPosition;
layout(location = 3) in vec3 vertexNormal;

out vec3 worldNormal;

uniform mat4 VP;
uniform mat4 Model;

void main()
{
	
	mat4 MVP = Model * VP;
	worldNormal = normalize(Model*vec4(vertexNormal,0.0f)).xyz;

	gl_Position = MVP * vec4(vertexPosition, 1.0);

}