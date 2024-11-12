#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUv;
uniform float time;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec3 Color;
out vec3 Normal;
out vec2 Uv;
void main()
{
    gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    Normal = aNormal;
    Uv = aUv;
}

#shader fragment
#version 330 core
in vec3 Normal;
in vec2 Uv;
uniform float time;
uniform sampler2D texture0;
uniform sampler2D texture1;
out vec4 FragCol;
void main()
{

    //vec4 texcol = textureLod(texture0, Uv, 1);
    vec4 texcol = texture(texture0,Uv);
    vec4 texcol1 = texture(texture1, Uv);
    FragCol = mix(texcol, texcol1, 0.5);
    //FragCol = texcol;
} 