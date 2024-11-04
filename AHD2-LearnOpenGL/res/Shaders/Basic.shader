#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 vertexCol;
layout (location = 2) in vec2 uv;
uniform float time;
out vec3 OutVertexCol;
out vec2 Outuv;
void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    OutVertexCol = vertexCol * (sin(time) * 0.5 + 0.5);
    Outuv = uv;
}

#shader fragment
#version 330 core
in vec3 OutVertexCol;
in vec2 Outuv;
uniform float time;
uniform sampler2D ourTexture;
out vec4 FragCol;
void main()
{
    //FragCol = vec4(OutVertexCol, 1.0f) * (sin(time) * 0.5 + 0.5) + (aaa * 0.1);
    //FragCol = vec4(OutVertexCol, 1.0f);
    vec4 texcol = texture(ourTexture, Outuv);
    FragCol = vec4(OutVertexCol.x, OutVertexCol.y, OutVertexCol.z, 1.0f) * texcol;
    FragCol = texcol;
    //FragCol = vec4(1.0f, 0.5f, 0.2f, 1.0f);
} 