#version 410 core

out vec4 FragColor;

uniform sampler2D tex0;

uniform sampler2D potolok;

in vec2 texCoord;

void main()
{
   
    FragColor = texture(tex0, texCoord);
}