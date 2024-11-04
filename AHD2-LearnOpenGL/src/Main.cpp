#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "vendor/stb_image/stb_image.h"
int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//打开核心模式

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(160 * 5, 90 * 5, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    //初始化glew
    if (glewInit() != GLEW_OK)
    {
        std::cout << "error!" << std::endl;
        return -1;
    }
    std::cout << glGetString(GL_VERSION) << std::endl;
    {
        float vertices[] = {
        0.0f, 1.0f,   0.8f, 0.0f, 0.0f,   0.5f, 1.0f,  //0(位置， 颜色， uv)
        1.0f, 0.0f,   0.0f, 0.6f, 0.0f,   1.0f, 0.5f,  //1
        -1.0f, -1.0f, 0.0f, 0.0f, 0.8f,   0.0f, 0.0f,  //2
        -0.4f, 0.8f,  0.5f, 0.5f, 0.0f,   0.3f, 0.9f   //3
        };

        unsigned int indices[] = {
            0, 1, 2, //第一个三角形
            2, 3 ,0  //第二个三角形
        };

        VertexBuffer vbo(vertices, 7 * 4 * sizeof(float));//创建一个vbo(创建的时候直接绑定了)

        VertexArray vao;
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(3);
        layout.Push<float>(2);
        vao.AddAtrrib(vbo, layout);

        IndexBuffer ibo(indices, 6);//创建一个ibo

        Shader shader("res/Shaders/Basic.shader");//直接包含了shader的创建链接启用等等

        vao.UnBind();
        ibo.UnBind();
        vbo.UnBind();

        Texture tex0("res/Textures/container.jpg", GL_RGB);
        Texture tex1("res/Textures/awesomeface.png", GL_RGBA);
        tex0.Bind(0);
        tex1.Bind(1);
        
        shader.SetUniformIndex("texture0", 0);
        shader.SetUniformIndex("texture1", 1);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//绘制模式更改为线框模式

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//清空屏幕用的颜色，状态设置函数
            glClear(GL_COLOR_BUFFER_BIT);//状态使用函数，清空屏幕
            
            float timeValue = glfwGetTime();
            shader.SetUniform1f("time", timeValue);

            vao.Bind();

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}