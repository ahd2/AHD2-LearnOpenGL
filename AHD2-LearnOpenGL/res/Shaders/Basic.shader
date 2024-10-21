#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 vertexCol;

out vec3 OutVertexCol;
void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    OutVertexCol = vertexCol;
}

#shader fragment
#version 330 core
in vec3 OutVertexCol;
out vec4 FragColor;

void main()
{
    FragColor = vec4(OutVertexCol, 1.0f);
    //FragColor = vec4(OutVertexCol.x, OutVertexCol.y, OutVertexCol.z, 1.0f);
    //FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
} 