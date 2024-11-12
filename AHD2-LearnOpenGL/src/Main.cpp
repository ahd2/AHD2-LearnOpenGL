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

//全局变量
float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间
//屏幕宽高
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
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//打开核心模式

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

    //初始化glew
    if (glewInit() != GLEW_OK)
    {
        std::cout << "error!" << std::endl;
        return -1;
    }
    std::cout << glGetString(GL_VERSION) << std::endl;
    {
        Shader shader("res/Shaders/Basic.shader");//直接包含了shader的创建链接启用等等

        Texture tex0("res/Textures/container.jpg", GL_RGB);
        Texture tex1("res/Textures/awesomeface.png", GL_RGBA);
        tex0.Bind(0);
        tex1.Bind(1);
        
        shader.SetUniformIndex("texture0", 0);
        shader.SetUniformIndex("texture1", 1);

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//绘制模式更改为线框模式
        glEnable(GL_DEPTH_TEST);//启用深度测试

        //定义相机
        glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
        Camera camera(cameraPos, 45.0f, 0.1f, 100.0f, screenWidth, screenHeight);

        //投影矩阵
        glm::mat4 projection = camera.GetProjectionMatrix();
        shader.SetUniformMatrix4fv("projection", projection);

        glm::vec3 position = glm::vec3(0, 0, 0);
        Model model("res/Models/box.obj", position);

        //鼠标移动配置
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetCursorPosCallback(window, mouse_callback);

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            //更新deltaTime
            float currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            //处理输入
            processCameraInputs(window, camera, deltaTime);
            //每帧计算鼠标偏移，而不是在回调函数里面计算
            xoffset = currentX - lastX;
            yoffset = lastY - currentY;
            lastX = currentX;
            lastY = currentY;
            camera.ProcessMouseMovement(xoffset,yoffset);

            /* Render here */
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//清空屏幕用的颜色，状态设置函数
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//状态使用函数，清空屏幕
            
            float timeValue = glfwGetTime();
            shader.SetUniform1f("time", timeValue);

            //观察矩阵
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

            //按下esc键退出渲染循环
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