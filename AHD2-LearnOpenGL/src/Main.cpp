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
#include "Camera.h"
#include "Input.h"
#include "Model.h"

//ȫ�ֱ���
float deltaTime = 0.0f; // ��ǰ֡����һ֡��ʱ���
float lastFrame = 0.0f; // ��һ֡��ʱ��
//��Ļ���
const int screenWidth = 160 * 5;
const int screenHeight = 90 * 5;
float lastX = screenWidth * 0.5f, lastY = screenHeight * 0.5f;
float currentX = screenWidth * 0.5f, currentY = screenHeight * 0.5f;
float xoffset = 0.0f, yoffset = 0.0f;

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
        Shader shader("res/Shaders/Basic.shader");//ֱ�Ӱ�����shader�Ĵ����������õȵ�

        Texture tex0("res/Textures/container.jpg", GL_RGB);
        Texture tex1("res/Textures/awesomeface.png", GL_RGBA);
        tex0.Bind(0);
        tex1.Bind(1);
        
        shader.SetUniformIndex("texture0", 0);
        shader.SetUniformIndex("texture1", 1);

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//����ģʽ����Ϊ�߿�ģʽ
        glEnable(GL_DEPTH_TEST);//������Ȳ���

        //�������
        glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
        Camera camera(cameraPos, 45.0f, 0.1f, 100.0f, screenWidth, screenHeight);

        //ͶӰ����
        glm::mat4 projection = camera.GetProjectionMatrix();
        shader.SetUniformMatrix4fv("projection", projection);

        glm::vec3 position = glm::vec3(0, 0, 0);
        Model model("res/Models/box.obj", position);

        //����ƶ�����
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetCursorPosCallback(window, mouse_callback);

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            //����deltaTime
            float currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            //��������
            processCameraInputs(window, camera, deltaTime);
            //ÿ֡�������ƫ�ƣ��������ڻص������������
            xoffset = currentX - lastX;
            yoffset = lastY - currentY;
            lastX = currentX;
            lastY = currentY;
            camera.ProcessMouseMovement(xoffset,yoffset);

            /* Render here */
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//�����Ļ�õ���ɫ��״̬���ú���
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//״̬ʹ�ú����������Ļ
            
            float timeValue = glfwGetTime();
            shader.SetUniform1f("time", timeValue);

            //�۲����
            glm::mat4 view = camera.GetViewMatrix();
            shader.SetUniformMatrix4fv("view", view);

            model.Draw(shader);
            /*for (unsigned int i = 0; i < 10; i++)
            {
                glm::mat4 model;
                model = glm::translate(model, cubePositions[i]);
                float angle = 20.0f * (i + 1);
                model = glm::rotate(model, timeValue * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                shader.SetUniformMatrix4fv("model", model);

                glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);
            }*/

            /* Swap front and back buffers */
            glfwSwapBuffers(window);
            /* Poll for and process events */
            glfwPollEvents();

            //����esc���˳���Ⱦѭ��
            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            {
                break;
            }
        }
    }
    glfwTerminate();
    return 0;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    currentX = xpos;
    currentY = ypos;
}