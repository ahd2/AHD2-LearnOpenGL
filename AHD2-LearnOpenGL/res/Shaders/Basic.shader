#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aUv;
uniform float time;
out vec3 Color;
out vec2 Uv;
void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    Color = aColor * (sin(time) * 0.5 + 0.5);//省计算次数
    Uv = aUv;
}

#shader fragment
#version 330 core
in vec3 Color;
in vec2 Uv;
uniform float time;
uniform sampler2D texture0;
uniform sampler2D texture1;
out vec4 FragCol;
void main()
{
    //FragCol = vec4(OutVertexCol, 1.0f) * (sin(time) * 0.5 + 0.5) + (aaa * 0.1);
    //FragCol = vec4(OutVertexCol, 1.0f);
    vec4 texcol = texture(texture0, Uv);
    vec4 texcol1 = texture(texture1, Uv);
    FragCol = vec4(Color, 1.0f);
    FragCol = mix(texcol, texcol1, 0.5);
    //FragCol = vec4(1.0f, 0.5f, 0.2f, 1.0f);
} 