#include<iostream>
#include"glad/glad.h"
#include<GLFW\glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"

using namespace std;

unsigned int CreateMesh(float* vertices, int nVertices, unsigned int* indices, int nIndices);
unsigned int CreateProgram(const char* VertexShaderSource, const char* FragmentShaderSource);
void RenderCompactProfile();
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void GLMPractice()
{  
    /*
    {
        glm::vec3 vec(100.0f, 0.0f, 0.0f);
        glm::vec3 vec1(50.0f, 50.0f, 0.0f);

        vec = glm::normalize(vec);
        vec1 = glm::normalize(vec1);
        std::cout << "outputVec : " << glm::to_string(vec) << std::endl;
        std::cout << "outputVec : " << glm::to_string(vec1) << std::endl;

        float angle = glm::dot(vec, vec1);

        std::cout << "Anlge : " << glm::acos(angle) * (180.0f / glm::pi<float>()) << std::endl;

        glm::vec2 x(1.0, 0.0);
        glm::vec2 y(-1.0, -1.0);
        y = glm::normalize(y);

        float a = glm::dot(x, y);

        std::cout << "Anlge : " << a << ": " << glm::acos(a) * (180.0f / glm::pi<float>()) << std::endl;
    }
    {
        glm::vec3 x(1.0, 0.0, 0.0);
        glm::vec3 y(0.0, 0.0, 1.0);

        glm::vec3 z = glm::cross(y, x);
        std::cout << "Cross Product : " << glm::to_string(z) << std::endl;
    }*/
    {
        glm::vec4 pos1(1.0f, 0.0f, 0.0f, 1.0f);
        glm::vec4 pos2(1.0f, 1.0f, 0.0f, 1.0f);


        glm::mat4 mat1 = glm::mat4(1.0f);
        mat1 = glm::translate(mat1, glm::vec3(0.0f, 2.0f, 0.0f));
        mat1 = glm::rotate(mat1, 45.0f, glm::vec3(0.0f, 0.0f, 1.0f));
        mat1 = glm::rotate(mat1, 35.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        mat1 = glm::scale(mat1, glm::vec3(2.0f, 2.0f, 2.0f));
        std::cout << "mat1 : " << glm::to_string(mat1) << std::endl;

        glm::mat4 mat2 = glm::mat4(1.0f);
        std::cout << "mat2 : " << glm::to_string(mat2) << std::endl;

        glm::vec4 outPos = mat1 * pos1;
        glm::vec4 outPos2 = mat1 * pos2;
        std::cout << "outPos : " << glm::to_string(outPos) << std::endl;
        std::cout << "outPos2 : " << glm::to_string(outPos2) << std::endl;

        /*
        glm::mat4 out = mat1 * mat2;
        std::cout << "out : " << glm::to_string(out) << std::endl;

        glm::mat4 out1 = mat2 * mat1;
        std::cout << "out1 : " << glm::to_string(out1) << std::endl;*/

    }

    int i;
    std::cin >> i;
}

float g_fScale = 1.0f;

unsigned int LoadTexture(std::string filePath)
{
    stbi_set_flip_vertically_on_load(true);
    int width, height, nrChannels;
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);

    if (data)
    {
        std::cout << "Image Loaded : " << width << ", " << height << ", Channels : " << nrChannels << std::endl;
    }
    else
    {
        std::cout << "Could not load image" << std::endl;
        return 0;
    }

    GLenum format = GL_RGB;
    if (nrChannels == 3)
        format = GL_RGB;
    else if (nrChannels == 4)
        format = GL_RGBA;

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Mirrored Repeat
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    // Clamp to Edge
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Clamp to Border
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    //float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    //glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // Trilinear filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR); 

    glGenerateMipmap(GL_TEXTURE_2D);

    if(data)
        stbi_image_free(data);

    return texture;
}

int main()
{
    glfwInit();
    // State setting function : GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    int width = 900;
    int height = 900;

    GLFWwindow* window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
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

    glfwSetScrollCallback(window, scroll_callback);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // TODO: Revisit once triangle is drawn
    glViewport(0, 0, width, height);
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Alpha Blend
    //glBlendFunc(GL_ONE, GL_ZERO); // Replace Blend
    glEnable(GL_DEPTH_TEST);

    float vertices[] = {
        // position             // texture-coordinates
        -0.5f, -0.5f, 0.0f,     -0.01f, -0.01f,  // top left
        -0.5f, 0.5f, 0.0f,      -0.01f, 1.01f,   // bottom left
         0.5f, -0.5f, 0.0f,     1.01f, -0.01f,  // bottom right
         0.5f, 0.5f, 0.0f,      1.01f, 1.01f    // top right
    };

    unsigned int indices[] = {
        0, 2, 1, 3
    };

    unsigned int mesh = CreateMesh(vertices, sizeof(vertices) / sizeof(float), indices, sizeof(indices) / sizeof(unsigned int));
    
    float verticeRectangle[] = {
        // position               // UV  
        -0.5f, -0.5f, 0.0f,       0.0f, 0.0f, // bottom left
         0.5f, -0.5f, 0.0f,       1.0f, 0.0f, // bottom right
         0.0f, 0.5f, 0.0f,        0.5f, 1.0f // top middle
    };

    unsigned int indicesRectangle[] = {
        0, 1, 2
    };

    unsigned int meshRectangle = CreateMesh(verticeRectangle, sizeof(verticeRectangle) / sizeof(float), indicesRectangle, sizeof(indicesRectangle) / sizeof(unsigned int));
    
    const char* VertexShaderSource = 
        "#version 330 core\n"
        "layout(location = 0) in vec3 aPosition;\n"
        "layout(location = 1) in vec2 aTexCoord; // UV \n"

        "uniform float uScale;\n"
        "uniform vec3 uOffset;\n"

        "out vec2 outUV;\n"

        "uniform mat4 uCombinedTransform;\n"

        "void main()\n"
        "{\n"
        "    vec4 vertexPos = uCombinedTransform * vec4(aPosition, 1.0);\n"
        "    gl_Position = vertexPos;\n"
        "    //gl_Position = vec4(aPosition*vec3(uScale) + uOffset, 1.0);\n"
        "    outUV = aTexCoord;\n"
        "}\n";

    const char* VertexShaderSourceSomething =
        "#version 330 core\n"
        "layout(location = 0) in vec3 aPosition;\n"

        "uniform vec3 uOffset;\n"

        "void main()\n"
        "{\n"
        "    gl_Position = vec4(aPosition + uOffset.yxz, 1.0);\n"
        "}\n";

    const char* FragmentShaderSource =
        "#version 330 core\n"
        "out vec4 FragColor;\n"

        "in vec2 outUV;\n"

        "uniform sampler2D texContainer;\n"
        "uniform sampler2D texMinion;\n"

        "uniform vec3 uColor;\n"

        "void main()\n"
        "{\n"
        "    vec4 colorContainer = texture(texContainer, outUV);\n"
        "    vec4 colorMinion = texture(texMinion, outUV);\n"
        "    vec3 color = colorMinion.rgb * colorMinion.a + colorContainer.rgb * (1 - colorMinion.a);\n"
        "    FragColor = vec4(color.rgb, colorContainer.a);\n"
        "}\n";

    unsigned int shaderProgram = CreateProgram(VertexShaderSource, FragmentShaderSource);
    unsigned int shaderProgramSomething = CreateProgram(VertexShaderSourceSomething, FragmentShaderSource);

    unsigned int textureContainer = LoadTexture("..\\media\\textures\\container.jpg");
    unsigned int textureMinion = LoadTexture("..\\media\\textures\\minion.png");

    while (!glfwWindowShouldClose(window))
    {
        // State Setting function
        glClearColor(0.0f, 0.3f, 0.2f, 1.0f);
        // State Using function
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float timeValue = (float)glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        float scale = (sin(timeValue * 0.2f)*0.5f) + 0.0f;

        glUseProgram(shaderProgram);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureContainer);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textureMinion);
        {
            glm::mat4 transform = glm::mat4(1.0f);
            transform = glm::translate(transform, glm::vec3(scale, 0.0f, 0.0f));
            //transform = glm::rotate(transform, scale, glm::vec3(0.0f, 0.0f, 1.0f));
            //transform = glm::scale(transform, glm::vec3(scale*2.0, scale*2.0f, 1.0f));
            int combinedTrasLocation = glGetUniformLocation(shaderProgram, "uCombinedTransform");
            glUniformMatrix4fv(combinedTrasLocation, 1, false, glm::value_ptr(transform));

            int scaleLocation = glGetUniformLocation(shaderProgram, "uScale");
            glUniform1f(scaleLocation, scale);

            int colorLocation = glGetUniformLocation(shaderProgram, "uColor");
            glUniform3f(colorLocation, 0.0f, greenValue, 1.0f);

            int offsetLocation = glGetUniformLocation(shaderProgram, "uOffset");
            glUniform3f(offsetLocation, 0.0f, 0.0f, 0.0f);

            int texContainerLocation = glGetUniformLocation(shaderProgram, "texContainer");
            glUniform1i(texContainerLocation, 0);

            int texMinionLocation = glGetUniformLocation(shaderProgram, "texMinion");
            glUniform1i(texMinionLocation, 1);
        }
        glBindVertexArray(mesh);
        {
            //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);      // If you have just VBOs
            glDrawElements(GL_TRIANGLE_STRIP, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0); // If you have EBOs defined
        }
        /*
        glUseProgram(shaderProgram);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureContainer);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textureMinion);
        {
            int colorLocation = glGetUniformLocation(shaderProgram, "uColor");
            glUniform3f(colorLocation, 0.0f, 0.0f, greenValue);

            int offsetLocation = glGetUniformLocation(shaderProgram, "uOffset");
            glUniform3f(offsetLocation, 0.5f, -0.3f, 0.0f);

            int texContainerLocation = glGetUniformLocation(shaderProgram, "texContainer");
            glUniform1i(texContainerLocation, 0);

            int texMinionLocation = glGetUniformLocation(shaderProgram, "texMinion");
            glUniform1i(texMinionLocation, 1);
        }
        glBindVertexArray(meshRectangle);
        {
            glDrawElements(GL_TRIANGLE_STRIP, sizeof(indicesRectangle) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
        }*/

        // Double buffering 
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

unsigned int CreateMesh(float * vertices, int nVertices, unsigned int * indices, int nIndices)
{
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    {
        // Creating Vertex Buffer Object
        int y = sizeof(vertices);
        unsigned int VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * nVertices, vertices, GL_STATIC_DRAW);

        // location 0, read 3 GL_FLOAT and jump(stride) 3 * sizeof(float) and offset is 0
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(0 * sizeof(float)));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // location 2, read 3 GL_FLOAT and jump(stride) 4 * sizeof(float) and offset is 1
        // glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(1 * sizeof(float)));
        // glEnableVertexAttribArray(0);
        //glBindBuffer(GL_ARRAY_BUFFER, 0);

        int x = sizeof(indices);
        unsigned int EBO;
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * nIndices, indices, GL_STATIC_DRAW);
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    glBindVertexArray(0);

    return VAO;
}

unsigned int CreateVertexShader(const char* VertexShaderSource)
{
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
    return vertexShader;
}

unsigned int CreateFragmentShader(const char* FragmentShaderSource)
{
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &FragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    int  success;
    char infoLog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    return fragmentShader;
}

unsigned int CreateProgram(const char* VertexShaderSource, const char* FragmentShaderSource)
{
    unsigned int vertexShader = CreateVertexShader(VertexShaderSource);
    unsigned int fragmentShader = CreateFragmentShader(FragmentShaderSource);

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    int  success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
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

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    g_fScale -= (float)yoffset*0.1f;
    if (g_fScale <= 0.0f)
        g_fScale = 0.01f;
    if (g_fScale > 5.0f)
        g_fScale = 5.0f;

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