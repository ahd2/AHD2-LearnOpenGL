#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

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
                //切换shader模式为顶点着色器
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                //切换模式为片元
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

    //检测编译是否成功
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
    //初始化glew
    if (glewInit() != GLEW_OK)
    {
        std::cout << "error!" << std::endl;
        return -1;
    }
    std::cout << glGetString(GL_VERSION) << std::endl;

    float vertices[] = {
    0.0f, 1.0f,   0.8f, 0.0f, 0.0f,//0(位置， 颜色)
    1.0f, 0.0f,   0.0f, 0.6f, 0.0f,//1
    -1.0f, -1.0f, 0.0f, 0.0f, 0.8f,//2
    -0.4f, 0.8f,  0.5f, 0.5f, 0.0f//3
    };

    unsigned int indices[] = {
        0, 1, 2, //第一个三角形
        2, 3 ,0  //第二个三角形
    };

    unsigned int buffer;
    //生成一个缓冲区
    glGenBuffers(1, &buffer);
    //指定为顶点缓冲区
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    //填充当前绑定的缓冲区（即上面的顶点缓冲区）
    glBufferData(GL_ARRAY_BUFFER, 5 * 4 * sizeof(float), vertices, GL_STATIC_DRAW);
    //指定数据格式
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);//指定位置属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 2));//指定颜色属性
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    unsigned int ebo;
    //生成一个缓冲区
    glGenBuffers(1, &ebo);//1表示创建的buffer数量
    //指定为索引缓冲区
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    //填充当前绑定的缓冲区（即上面的顶点缓冲区）
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    //拿出shader源码
    ShaderProgramSource shadersource =  ParseShader("res/Shaders/Basic.shader");

    //创建一个程序对象(其中直接包含shader的创建，编译，程序的链接启用)
    unsigned int shaderProgram = CreateShader(shadersource.VertexSource, shadersource.FragmentSource);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//绘制模式更改为线框模式

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//清空屏幕用的颜色，状态设置函数
        glClear(GL_COLOR_BUFFER_BIT);//状态使用函数，清空屏幕
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    //glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}