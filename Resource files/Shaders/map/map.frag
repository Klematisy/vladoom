#version 410 core

out vec4 FragColor;

uniform sampler2D tex1;
uniform sampler2D tex2;
uniform sampler2D tex3;
uniform sampler2D tex4;
uniform sampler2D door;

uniform sampler2D potolok;

in vec2 texCoord;
flat in int texId;

void main()
{
    if (texId == 1)
        FragColor = texture(tex1, texCoord);
    else if (texId == 2)
        FragColor = texture(tex2, texCoord);
    else if (texId == 3)
        FragColor = texture(tex3, texCoord);
    else if (texId == 4)
        FragColor = texture(tex4, texCoord);
    else if (texId == 9)
        FragColor = texture(door, texCoord);
    else if (texId == 17)
        FragColor = vec4(0.5, 0.5, 0.5, 1.0);
    else if (texId == 18)
        FragColor = vec4(0.3, 0.3, 0.3, 1.0);
    else if (texId == 19)
        FragColor = texture(potolok, texCoord);
}