#version 410 core

out vec4 FragColor;

uniform sampler2D tex0;

in vec2 texCoord;

void main()
{
   // FragColor = vec4(1.0, 1.0, 1.0, 1.0);
   FragColor = texture(tex0, texCoord);
}