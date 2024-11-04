#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

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

        //纹理
        unsigned int texture;
        glGenTextures(1, &texture);
        glActiveTexture(GL_TEXTURE0);//0号默认激活
        glBindTexture(GL_TEXTURE_2D, texture);
        // 为当前绑定的纹理对象设置环绕、过滤方式
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //加载图像
        int width, height, nrChannels;
        unsigned char* data = stbi_load("res/Textures/container.jpg", &width, &height, &nrChannels, 0);
        if (data)
        {
            //往纹理buffer填充数据
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        //释放图像内存（cpu端）
        stbi_image_free(data);

        unsigned int texture1;
        glGenTextures(1, &texture1);
        glActiveTexture(GL_TEXTURE1);//激活一号纹理单元（插槽）
        glBindTexture(GL_TEXTURE_2D, texture1);
        // 为当前绑定的纹理对象设置环绕、过滤方式
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //加载图像
        int width1, height1, nrChannels1;
        unsigned char* data1 = stbi_load("res/Textures/awesomeface.png", &width1, &height1, &nrChannels1, 0);
        if (data1)
        {
            //往纹理buffer填充数据
            //纹理目标、mipmap级别、纹理存储为什么格式、宽、高、源图格式，源图数据格式、数据
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGBA, GL_UNSIGNED_BYTE, data1);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        //释放图像内存（cpu端）
        stbi_image_free(data1);
        
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