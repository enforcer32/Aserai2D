#version 460 core

layout (location = 0) in vec4 a_Position;
layout (location = 1) in vec4 a_Color;

out vec4 v_Color;

uniform mat4 u_ProjectionViewMatrix;

void main()
{
	gl_Position = u_ProjectionViewMatrix * a_Position;
	v_Color = a_Color;
}
