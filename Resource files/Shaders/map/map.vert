#version 410 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTex;
// layout(location = 2) in int id;

out vec2 texCoord;
// flat out int texId;

uniform mat4 view;
uniform mat4 proj;

void main()
{
   gl_Position = proj * view * vec4(aPos, 1.0);
   texCoord = aTex;
   // texId = id;
}