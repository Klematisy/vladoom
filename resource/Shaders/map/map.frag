#version 410 core

out vec4 FragColor;

uniform sampler2D tex0;
uniform sampler2D potolok;
in vec2 texCoord;
vec4 texColor;

void main()
{
    texColor = texture(tex0, texCoord);
    if (texColor.a < 0.1)  {// Игнорируем пиксели с низкой прозрачностью
        discard;
    }
    
    FragColor = texColor;
}