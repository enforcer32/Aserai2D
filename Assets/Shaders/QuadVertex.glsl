#version 460 core

layout (location = 0) in vec4 a_Position;
layout (location = 1) in vec4 a_Color;
layout (location = 2) in vec2 a_TextureUV;
layout (location = 3) in float a_TextureID;

out vec4 v_Color;
out vec2 v_TextureUV;
out flat float v_TextureID;

uniform mat4 u_ProjectionViewMatrix;

void main()
{
	gl_Position = u_ProjectionViewMatrix * a_Position;
	v_Color = a_Color;
	v_TextureUV = a_TextureUV;
	v_TextureID = a_TextureID;
}
