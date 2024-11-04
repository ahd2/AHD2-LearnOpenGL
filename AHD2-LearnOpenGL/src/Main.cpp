#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//�򿪺���ģʽ

    const int screenWidth = 160 * 5;
    const int screenHeight = 90 * 5;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(screenWidth, screenHeight, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    //glfwSwapInterval(1);

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

        Texture tex0("res/Textures/container.jpg", GL_RGB);
        Texture tex1("res/Textures/awesomeface.png", GL_RGBA);
        tex0.Bind(0);
        tex1.Bind(1);
        
        shader.SetUniformIndex("texture0", 0);
        shader.SetUniformIndex("texture1", 1);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//����ģʽ����Ϊ�߿�ģʽ

        //ģ�;���
        glm::mat4 model;
        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        //�۲����
        glm::mat4 view;
        // ע�⣬���ǽ�����������Ҫ�����ƶ������ķ������ƶ���
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        //ͶӰ����
        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), (float)screenWidth / screenHeight, 0.1f, 100.0f);

        shader.SetUniformMatrix4fv("model", model);
        shader.SetUniformMatrix4fv("view", view);
        shader.SetUniformMatrix4fv("projection", projection);

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//�����Ļ�õ���ɫ��״̬���ú���
            glClear(GL_COLOR_BUFFER_BIT);//״̬ʹ�ú����������Ļ
            
            float timeValue = glfwGetTime();
            shader.SetUniform1f("time", timeValue);

            model = glm::rotate(model,  glm::radians(0.5f), glm::vec3(0.5f, 1.0f, 0.0f));

            shader.SetUniformMatrix4fv("model", model);

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