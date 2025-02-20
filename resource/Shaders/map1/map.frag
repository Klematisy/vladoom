#version 410 core

out vec4 FragColor;

uniform sampler2D tex0;
in vec2 texCoord;
in float alpha;

void main()
{
    vec4 texColor = texture(tex0, texCoord);
    if (texColor.a < 0.1)
        discard;
    
    FragColor = vec4(texColor.rgb, texColor.a * alpha);
}