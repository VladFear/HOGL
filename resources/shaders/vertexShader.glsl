#version 330 core

layout (location = 0) in vec3 position;
out vec3 color;

uniform mat4 transform_matrix;

void main()
{
	gl_Position = transform_matrix * vec4(position, 1.0f);
	color = abs(position);
}
