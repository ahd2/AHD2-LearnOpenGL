#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);

    enum ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    ShaderType type = ShaderType::NONE;
    std::string line;
    std::stringstream ss[2];
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                //�л�shaderģʽΪ������ɫ��
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                //�л�ģʽΪƬԪ
                type = ShaderType::FRAGMENT;
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }
    return { ss[0].str(), ss[1].str()};
}

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);

    //�������Ƿ�ɹ�
    int  success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(sizeof(char) * length);
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER? "vertex" : "fragment") << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    glUseProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);
    
    return program;
}
template<int N>
class Array {
private:
    int m_Array[N];
};

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
        0.0f, 1.0f,   0.8f, 0.0f, 0.0f,//0(λ�ã� ��ɫ)
        1.0f, 0.0f,   0.0f, 0.6f, 0.0f,//1
        -1.0f, -1.0f, 0.0f, 0.0f, 0.8f,//2
        -0.4f, 0.8f,  0.5f, 0.5f, 0.0f//3
        };

        unsigned int indices[] = {
            0, 1, 2, //��һ��������
            2, 3 ,0  //�ڶ���������
        };

        VertexBuffer vbo(vertices, 5 * 4 * sizeof(float));//����һ��vbo(������ʱ��ֱ�Ӱ���)

        VertexArray vao;
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(3);
        vao.AddAtrrib(vbo, layout);

        ////����һ��vao����
        //unsigned int vao;
        //glGenVertexArrays(1, &vao);
        //glBindVertexArray(vao);
        ////ָ�����ݸ�ʽ
        //glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);//ָ��λ������
        //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 2));//ָ����ɫ����
        //glEnableVertexAttribArray(0);
        //glEnableVertexAttribArray(1);

        IndexBuffer ibo(indices, 6);//����һ��ibo

        //�ó�shaderԴ��
        ShaderProgramSource shadersource =  ParseShader("res/Shaders/Basic.shader");

        //����һ���������(����ֱ�Ӱ���shader�Ĵ��������룬�������������)
        unsigned int shaderProgram = CreateShader(shadersource.VertexSource, shadersource.FragmentSource);
        vao.UnBind();
        ibo.UnBind();
        vbo.UnBind();

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//����ģʽ����Ϊ�߿�ģʽ

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//�����Ļ�õ���ɫ��״̬���ú���
            glClear(GL_COLOR_BUFFER_BIT);//״̬ʹ�ú����������Ļ
            
            float timeValue = glfwGetTime();
            int timeLocation = 0;//glGetUniformLocation(shaderProgram, "time");
            glUniform1f(timeLocation, timeValue);

            vao.Bind();

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

        //glDeleteProgram(shaderProgram);
    }
    glfwTerminate();
    return 0;
}