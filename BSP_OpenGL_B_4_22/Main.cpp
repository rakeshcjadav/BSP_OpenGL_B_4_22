#include<iostream>
#include<vector>
#include"glad/glad.h"
#include<GLFW\glfw3.h>
#include"GLM.h"
#include"Mesh.h"
#include"Program.h"

#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"

using namespace std;

CMesh * CreateMesh(const SMeshData & meshData);
CProgram * CreateProgram(const char* VertexShaderSource, const char* FragmentShaderSource);
void RenderCompactProfile();
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouseButton_callback(GLFWwindow* window, int button, int action, int mods);

void processInput(GLFWwindow * window);


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
glm::vec3 g_vCameraPos = glm::vec3(0.0f, 0.0f, 10.0f);
glm::vec3 g_vCameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 g_vCameraUp = glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f));

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

    int width = 1280;
    int height = 720;

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
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouseButton_callback);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // TODO: Revisit once triangle is drawn
    glViewport(0, 0, width, height);
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Alpha Blend
    //glBlendFunc(GL_ONE, GL_ZERO); // Replace Blend
    glEnable(GL_DEPTH_TEST);

    CMesh * pPlaneMesh = CreateMesh(SMeshData(SMeshData::MESH_TYPE::PLANE_MESH));
    CMesh * pCubeMesh = CreateMesh(SMeshData(SMeshData::MESH_TYPE::CUBE_MESH));

    const char* VertexShaderSource = 
        "#version 330 core\n"
        "layout(location = 0) in vec3 aPosition;\n"
        "layout(location = 1) in vec2 aTexCoord; // UV \n"
        "layout(location = 2) in int colorID;\n"

        "uniform float uScale;\n"
        "uniform vec3 uOffset;\n"

        "out vec2 outUV;\n"
        "flat out int outColorID;\n"

        "uniform mat4 uCombinedTransform;\n"
        "uniform mat4 uWorldMatrix;\n"
        "uniform mat4 uViewMatrix;\n"
        "uniform mat4 uProjectionMatrix;\n"

        "void main()\n"
        "{\n"
        "    vec4 vertexPos = uProjectionMatrix * uViewMatrix * uWorldMatrix * vec4(aPosition, 1.0);\n"
        "    gl_Position = vertexPos;\n"
        "    //gl_Position = vec4(aPosition*vec3(uScale) + uOffset, 1.0);\n"
        "    outUV = aTexCoord;\n"
        "    outColorID = colorID;\n"
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
        "flat in int outColorID;\n"

        "uniform sampler2D texContainer;\n"
        "uniform sampler2D texMinion;\n"

        "uniform vec3 uColor;\n"

        "const vec3 colors[6] = vec3[](\n"
            "vec3(1.0f, 0.0f, 0.0f),\n"
            "vec3(0.0f, 1.0f, 0.0f),\n"
            "vec3(0.0f, 0.0f, 1.0f),\n"
            "vec3(1.0f, 1.0f, 0.0f),\n"
            "vec3(0.0f, 1.0f, 1.0f),\n"
            "vec3(1.0f, 0.0f, 1.0f)\n"
        ");\n"

        "void main()\n"
        "{\n"
        "    vec4 colorContainer = texture(texContainer, outUV);\n"
        "    vec4 colorMinion = texture(texMinion, outUV);\n"
        "    vec3 color = colorMinion.rgb * colorMinion.a + colorContainer.rgb * (1 - colorMinion.a);\n"
        "    FragColor = vec4(color.rgb, colorContainer.a);\n"
        "    FragColor = vec4(colors[outColorID], 1.0);\n"
        "}\n";

    CProgram * pProgram = CreateProgram(VertexShaderSource, FragmentShaderSource);
    CProgram * pProgramSomething = CreateProgram(VertexShaderSourceSomething, FragmentShaderSource);

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

        pProgram->Use();
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureContainer);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textureMinion);
        {
            glm::mat4 matWorld = glm::mat4(1.0f);
            matWorld = glm::translate(matWorld, glm::vec3(0.0f, 0.0f, 0.0f));
            //matWorld = glm::rotate(matWorld, scale*5.0f, glm::vec3(1.0f, 1.0f, 0.0f));
            //matWorld = glm::scale(matWorld, glm::vec3(scale*2.0, scale*2.0f, 1.0f));

            glm::mat4 matProjection;
            matProjection = glm::perspective(glm::radians(60.0f), width / (height * 1.0f), 0.1f, 100.0f);

            glm::mat4 matWorldProjection = matProjection * matWorld;

            glm::mat4 matView = glm::mat4(1.0f);
            matView = glm::lookAt(g_vCameraPos, g_vCameraPos + g_vCameraFront, g_vCameraUp);

            pProgram->SetUniformMatrix("uCombinedTransform", matWorldProjection);
            pProgram->SetUniformMatrix("uWorldMatrix", matWorld);
            pProgram->SetUniformMatrix("uViewMatrix", matView);
            pProgram->SetUniformMatrix("uProjectionMatrix", matProjection);

            pProgram->SetUniformFloat("uScale", scale);

            pProgram->SetUniformColor("uColor", glm::vec3(0.0f, greenValue, 1.0f));
            pProgram->SetUniformColor("uOffset", glm::vec3(0.0f, 0.0f, 0.0f));
            

            pProgram->SetUniformInt("texContainer", 0);
            pProgram->SetUniformInt("texMinion", 1);
        }
        pCubeMesh->Render();
        {
            glm::mat4 matWorld = glm::mat4(1.0f);
            matWorld = glm::translate(matWorld, glm::vec3(3.0f, 0.0f, 0.0f));
            matWorld = glm::rotate(matWorld, scale * 5.0f, glm::vec3(1.0f, 1.0f, 0.0f));
            //matWorld = glm::scale(matWorld, glm::vec3(scale*2.0, scale*2.0f, 1.0f));

            pProgram->SetUniformMatrix("uWorldMatrix", matWorld);
        }
        pCubeMesh->Render();
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
        processInput(window);

        // Double buffering 
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

CMesh * CreateMesh(const SMeshData& meshData)
{
    return CMesh::CreateMesh(meshData);
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

CProgram * CreateProgram(const char* VertexShaderSource, const char* FragmentShaderSource)
{
   return CProgram::CreateProgram(VertexShaderSource, FragmentShaderSource);
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

bool g_bLookAround = false;
bool g_bfirstMouse = true;
double lastX, lastY;
float yaw = -90.0f, pitch = 0.0f;

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (!g_bLookAround)
        return;
    if (g_bfirstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        g_bfirstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    g_vCameraFront = glm::normalize(direction);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    std::cout << "Key : ( " << key << ", " << scancode << ", " << action << ", " << mods << " ) " << std::endl;
}

void mouseButton_callback(GLFWwindow* window, int button, int action, int mods)
{
    /*
    if (action == GLFW_PRESS)
    {
        if(button == 0)
            g_bLookAround = true;
    }
    else if (action = GLFW_RELEASE)
    {
        g_bLookAround = false;
    }
    */
}

void processInput(GLFWwindow* window)
{
    const float cameraSpeed = 0.05f; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        g_vCameraPos += cameraSpeed * g_vCameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        g_vCameraPos -= cameraSpeed * g_vCameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        g_vCameraPos -= glm::normalize(glm::cross(g_vCameraFront, g_vCameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        g_vCameraPos += glm::normalize(glm::cross(g_vCameraFront, g_vCameraUp)) * cameraSpeed;


    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        g_bLookAround = true;
    }
    else
    {
        g_bLookAround = false;
        g_bfirstMouse = true;
    }
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