#version 410 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTex;
layout(location = 2) in float aAlpha;

out vec2 texCoord;
out float alpha;

void main()
{
   gl_Position = vec4(aPos, 1.0);
   texCoord = aTex;
   alpha = aAlpha;
}