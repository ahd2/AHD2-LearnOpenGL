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
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//�򿪺���ģʽ

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(160 * 5, 90 * 5, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    //��ʼ��glew
    if (glewInit() != GLEW_OK)
    {
        std::cout << "error!" << std::endl;
        return -1;
    }
    std::cout << glGetString(GL_VERSION) << std::endl;
    {
        float vertices[] = {
        0.0f, 1.0f,   0.8f, 0.0f, 0.0f,   0.5f, 1.0f,  //0(λ�ã� ��ɫ�� uv)
        1.0f, 0.0f,   0.0f, 0.6f, 0.0f,   1.0f, 0.5f,  //1
        -1.0f, -1.0f, 0.0f, 0.0f, 0.8f,   0.0f, 0.0f,  //2
        -0.4f, 0.8f,  0.5f, 0.5f, 0.0f,   0.3f, 0.9f   //3
        };

        unsigned int indices[] = {
            0, 1, 2, //��һ��������
            2, 3 ,0  //�ڶ���������
        };

        VertexBuffer vbo(vertices, 7 * 4 * sizeof(float));//����һ��vbo(������ʱ��ֱ�Ӱ���)

        VertexArray vao;
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(3);
        layout.Push<float>(2);
        vao.AddAtrrib(vbo, layout);

        IndexBuffer ibo(indices, 6);//����һ��ibo

        Shader shader("res/Shaders/Basic.shader");//ֱ�Ӱ�����shader�Ĵ����������õȵ�

        vao.UnBind();
        ibo.UnBind();
        vbo.UnBind();

        //����
        unsigned int texture;
        glGenTextures(1, &texture);
        glActiveTexture(GL_TEXTURE0);//0��Ĭ�ϼ���
        glBindTexture(GL_TEXTURE_2D, texture);
        // Ϊ��ǰ�󶨵�����������û��ơ����˷�ʽ
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //����ͼ��
        int width, height, nrChannels;
        unsigned char* data = stbi_load("res/Textures/container.jpg", &width, &height, &nrChannels, 0);
        if (data)
        {
            //������buffer�������
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        //�ͷ�ͼ���ڴ棨cpu�ˣ�
        stbi_image_free(data);

        unsigned int texture1;
        glGenTextures(1, &texture1);
        glActiveTexture(GL_TEXTURE1);//����һ������Ԫ����ۣ�
        glBindTexture(GL_TEXTURE_2D, texture1);
        // Ϊ��ǰ�󶨵�����������û��ơ����˷�ʽ
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //����ͼ��
        int width1, height1, nrChannels1;
        unsigned char* data1 = stbi_load("res/Textures/awesomeface.png", &width1, &height1, &nrChannels1, 0);
        if (data1)
        {
            //������buffer�������
            //����Ŀ�ꡢmipmap��������洢Ϊʲô��ʽ�����ߡ�Դͼ��ʽ��Դͼ���ݸ�ʽ������
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGBA, GL_UNSIGNED_BYTE, data1);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        //�ͷ�ͼ���ڴ棨cpu�ˣ�
        stbi_image_free(data1);
        
        shader.SetUniformIndex("texture1", 1);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//����ģʽ����Ϊ�߿�ģʽ

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//�����Ļ�õ���ɫ��״̬���ú���
            glClear(GL_COLOR_BUFFER_BIT);//״̬ʹ�ú����������Ļ
            
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