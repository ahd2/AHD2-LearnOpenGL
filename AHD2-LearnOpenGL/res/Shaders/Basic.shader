#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 vertexCol;
uniform float time;
out vec3 OutVertexCol;
void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    OutVertexCol = vertexCol * (sin(time) * 0.5 + 0.5);
}

#shader fragment
#version 330 core
in vec3 OutVertexCol;
uniform float time;
out vec4 FragCol;
void main()
{
    //FragCol = vec4(OutVertexCol, 1.0f) * (sin(time) * 0.5 + 0.5) + (aaa * 0.1);
    //FragCol = vec4(OutVertexCol, 1.0f);
    FragCol = vec4(OutVertexCol.x, OutVertexCol.y, OutVertexCol.z, 1.0f);
    //FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
} 