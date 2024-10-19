#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>
int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

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

    float vertices[] = {
    0.0f, 1.0f,
    1.0f, 0.0f,
    -1.0f, -1.0f
    };

    unsigned int buffer;
    //����һ��������
    glGenBuffers(1, &buffer);
    //ָ��Ϊ���㻺����
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    //��䵱ǰ�󶨵Ļ�������������Ķ��㻺������
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), vertices, GL_STATIC_DRAW);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}