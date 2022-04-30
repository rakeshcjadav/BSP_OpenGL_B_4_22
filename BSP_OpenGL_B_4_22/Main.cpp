#include<iostream>
#include"glad/glad.h"
#include<GLFW\glfw3.h>

using namespace std;

void RenderCompactProfile();

int main()
{
    glfwInit();
    // State setting function : GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // TODO: Revisit once triangle is drawn
    glViewport(0, 0, 800, 600);
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Alpha Blend
    //glBlendFunc(GL_ONE, GL_ZERO); // Replace Blend
    glEnable(GL_DEPTH_TEST);

    float vertices[] = {
        // position             // color
        -0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,       // top left
        -0.5f, 0.5f, 0.0f,      0.0f, 1.0f, 0.0f,       // bottom left
         0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,       // bottom right
         0.5f, 0.5f, 0.0f,      0.0f, 1.0f, 0.0f,       // top right

         -0.5f, 1.0f, 0.0f,      0.0f, 1.0f, 0.0f,        // top top right
          0.5f, 1.0f, 0.0f,      0.0f, 1.0f, 0.0f         // top top left
    };

    unsigned int indices[] = {
        0, 2, 1, 3, 4, 5
    };

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    {
        // Creating Vertex Buffer Object
        int y = sizeof(vertices);
        unsigned int VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // location 0, read 3 GL_FLOAT and jump(stride) 3 * sizeof(float) and offset is 0
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(0 * sizeof(float)));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // location 2, read 3 GL_FLOAT and jump(stride) 4 * sizeof(float) and offset is 1
        // glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(1 * sizeof(float)));
        // glEnableVertexAttribArray(0);
        //glBindBuffer(GL_ARRAY_BUFFER, 0);

        int x = sizeof(indices);
        unsigned int EBO;
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    glBindVertexArray(0);

    const char* VertexShaderSource = 
        "#version 330 core\n"
        "layout(location = 0) in vec3 aPosition;\n"
        "layout(location = 1) in vec3 aColor;\n"

        "//out vec3 outColor;\n"

        "uniform float uSomething;\n"

        "//uniform vec3 uColor;\n"

        "uniform vec3 uColors[3];\n"

        "float Offset = 0.2;\n"
        "vec3 vOffset = vec3(0.2, 0.0, 0.2);\n"

        "vec3 vScale = vec3(2.0, 2.0, 0.0);\n"

        "void main()\n"
        "{\n"
        "    vec3 newPos = aPosition * vec3(uSomething) + vec3(uSomething, 0.0, 0.0);\n"
        "    gl_Position = vec4(newPos.xyz, 1.0);\n"
        "    //outColor = uColor;\n"
        "}\n";

    //=> vecn => .x, .y, .z, .w => Position
    //=> vecn => .r, .g, .b, .a => Color
    //=> vecn => .s, .t, .p, .q => Texture Coordinate

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &VertexShaderSource, NULL);
    glCompileShader(vertexShader);
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    const char* FragmentShaderSource =
        "#version 330 core\n"
        "out vec4 FragColor;\n"

        "//in vec3 outColor;\n"

        "uniform vec3 uColor;\n"

        "void main()\n"
        "{\n"
        "    FragColor = vec4(uColor, 1.0f);\n"
        "}\n";

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &FragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) 
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glUseProgram(shaderProgram);

    int somethingLocation = glGetUniformLocation(shaderProgram, "uSomething");
    glUniform1f(somethingLocation, 0.0f);

    int colorLocation = glGetUniformLocation(shaderProgram, "uColor");
    glUniform3f(colorLocation, 0.0f, 0.0f, 1.0f);


    while (!glfwWindowShouldClose(window))
    {
        // State Setting function
        glClearColor(0.0f, 0.3f, 0.2f, 1.0f);
        // State Using function
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;

        glUseProgram(shaderProgram);
        //int colorLocation = glGetUniformLocation(shaderProgram, "uColor");
        glUniform3f(colorLocation, 0.0f, greenValue, 1.0f);

        //float color[9] = {0.0f, greenValue, 1.0f, 0.0f, greenValue, 1.0f , 0.0f, greenValue, 1.0f };
        //glUniform3fv(colorLocation, 3, color);

        //int somethingLocation = glGetUniformLocation(shaderProgram, "uSomething");
        glUniform1f(somethingLocation, greenValue);

        glBindVertexArray(VAO);

        //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);      // If you just VBOs
        glDrawElements(GL_TRIANGLE_STRIP, sizeof(indices)/sizeof(unsigned int), GL_UNSIGNED_INT, 0); // If you have EBOs defined

        // Double buffering 
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void RenderCompactProfile()
{
    // Red Quad
    glBegin(GL_TRIANGLE_STRIP);
///glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 0.5f, 0.10f);  // 0
  //      glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 0.0f, 0.10f);  // 1
        glVertex3f(0.5f, 0.5f, 0.10f);  // 3
        glVertex3f(0.5f, 0.0f, 0.10f);  // 2
    glEnd();

    // Blue
    glBegin(GL_TRIANGLES);
        glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
        glVertex3f(-0.5f, 0.1f, 0.05f);
        glVertex3f(0.0f, -0.5f, 0.05f);
        glVertex3f(0.5f, 0.1f, 0.05f);
    glEnd();
}

// E.g.
// vec2 someVec = vec2(1.0, 2.0);
// Case: 1
// vec4 differentVec = someVec.xyxx;
// differentVec.x = 1.0, differentVec.y = 2.0, differentVec.z = 1.0, differentVec.w = 1.0
// vec3 anotherVec = differentVec.zyw;
// anotherVec.x = 1.0, anotherVec.y = 2.0, anotherVec.z = 1.0
// vec4 otherVec = someVec.xxxx + anotherVec.yxzy;
//   otherVec.x = someVec.x + anotherVec.y;
// otherVec.x = 3.0, otherVec.y = 2.0, otherVec.z = 2.0, otherVec.w = 3.0
// otherVec = otherVec.xxxx;

// Case : 2
// vec4 differentVec = someVec.yxyy;
// differentVec.x = 2.0, differentVec.y = 1.0, differentVec.z = 2.0, differentVec.w = 2.0
// vec3 anotherVec = differentVec.zyw;
// anotherVec.x = 2.0, anotherVec.y = 1.0, anotherVec.z = 2.0

// Case : 3
// vec4 differentVec = someVec.xxxx;
// differentVec.x = 1.0, differentVec.y = 1.0, differentVec.z = 1.0, differentVec.w = 1.0
// vec3 anotherVec = differentVec.zyw;
// anotherVec.x = 1.0, anotherVec.y = 1.0, anotherVec.z = 1.0