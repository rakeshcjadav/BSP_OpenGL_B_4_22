#include<iostream>
#include<vector>
#include"glad/glad.h"
#include<GLFW\glfw3.h>
#include"GLM.h"
#include"MeshFilter.h"
#include"Program.h"
#include"Texture.h"
#include"Scene.h"
#include"Object.h"
#include"MeshRenderer.h"
#include"Material.h"
#include"Camera.h"
#include"Transform.h"
#include"PointLight.h"

using namespace std;

CMeshFilter* CreateMesh(const SMeshData& meshData)
{
    return CMeshFilter::CreateMesh(meshData);
}

CProgram* CreateProgram(const char* VertexShaderSource, const char* FragmentShaderSource)
{
    return CProgram::CreateProgram(VertexShaderSource, FragmentShaderSource);
}

CTexture* LoadTexture(std::string filePath)
{
    return CTexture::CreateTexture(filePath.c_str());
}

void RenderCompactProfile();

// GLFW Call backs
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouseButton_callback(GLFWwindow* window, int button, int action, int mods);

// Input processing
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
bool g_bLookAround = false;
bool g_bfirstMouse = true;
double lastX, lastY;
float yaw = -90.0f, pitch = 0.0f;
CCamera* g_pCamera = nullptr;

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
    
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW); // Counter Clockwise
    //glFrontFace(GL_CW); // Clockwise
    glCullFace(GL_BACK);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Alpha Blend
    //glBlendFunc(GL_ONE, GL_ZERO); // Replace Blend
    glEnable(GL_DEPTH_TEST);

    //CAssetManager::Instance().GetProgram("defaultProgram");

    CProgram * pUnlitProgram = CreateProgram("..\\media\\shaders\\vertex_shader.vert", "..\\media\\shaders\\fragment_shader.frag");
    CProgram* pLitProgram = CreateProgram("..\\media\\shaders\\vertex_shader_lit.vert", "..\\media\\shaders\\fragment_shader_lit.frag");

    CMeshFilter* pCubeMeshFilter = CMeshFilter::CreateMesh(SMeshData(SMeshData::MESH_TYPE::CUBE_MESH));
    CMeshFilter* pPlaneMeshFilter = CMeshFilter::CreateMesh(SMeshData(SMeshData::MESH_TYPE::PLANE_MESH));

    SMaterialProperties material = { {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, 256.0f };

    CMaterial* pUnlitMaterial = CMaterial::CreateMaterial("UnlitMaterial", material);
    pUnlitMaterial->SetProgram(pUnlitProgram);
    pUnlitMaterial->AddTexture(LoadTexture("..\\media\\textures\\container.jpg"));
    pUnlitMaterial->AddTexture(LoadTexture("..\\media\\textures\\minion.png"));

    CMaterial* pLitMaterial = CMaterial::CreateMaterial("LitMaterial", material);
    pLitMaterial->SetProgram(pLitProgram);
    pLitMaterial->AddTexture(LoadTexture("..\\media\\textures\\container.jpg"));
    pLitMaterial->AddTexture(LoadTexture("..\\media\\textures\\container2_specular.png"));

    CMaterial* pLitMaterialCrate = CMaterial::CreateMaterial("LitMaterialCrate", material);
    pLitMaterialCrate->SetProgram(pLitProgram);
    pLitMaterialCrate->AddTexture(LoadTexture("..\\media\\textures\\container2.png"));
    pLitMaterialCrate->AddTexture(LoadTexture("..\\media\\textures\\container2_specular.png"));

    //CAssetManager::Instance().GetMeshRenderer("PLANE", "CubeMaterial");
    // Scene
    CScene* pScene = CScene::CreateScene("MainScene");
    CTransform* pCubeTransform = nullptr;
    {
        // Cube
        CMeshRenderer* pMeshRenderer = CMeshRenderer::Create();
        pMeshRenderer->SetMeshFilter(pCubeMeshFilter);
        pMeshRenderer->SetMaterial(pLitMaterialCrate);
        CObject* pCubeObject = CObject::CreateObject("Cube");
        pCubeObject->SetMeshRenderer(pMeshRenderer);
        pScene->AddObject(pCubeObject, CTransform::CreateTransform(glm::vec3(5.0f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(2.0f)));
        pCubeTransform = pCubeObject->GetTransform();
    }
    {
        // Cube 2
        CMeshRenderer* pMeshRenderer = CMeshRenderer::Create();
        pMeshRenderer->SetMeshFilter(pCubeMeshFilter);
        pMeshRenderer->SetMaterial(pLitMaterialCrate);
        CObject* pCubeObject = CObject::CreateObject("Cube 2");
        pCubeObject->SetMeshRenderer(pMeshRenderer);
        pScene->AddObject(pCubeObject, CTransform::CreateTransform(glm::vec3(-5.0f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(2.0f)));
    }
    {
        // Ground plane
        CMeshRenderer* pPlaneMeshRenderer = CMeshRenderer::Create();
        pPlaneMeshRenderer->SetMeshFilter(pPlaneMeshFilter);
        pPlaneMeshRenderer->SetMaterial(pUnlitMaterial);
        CObject* pPlaneObject = CObject::CreateObject("Plane");
        pPlaneObject->SetMeshRenderer(pPlaneMeshRenderer);
        pScene->AddObject(pPlaneObject, CTransform::CreateTransform(glm::vec3(-5.0f, -2.0f, 0.0f), glm::vec3(-90.0f, 0.0f, 0.0f), glm::vec3(100.0f, 100.0f, 1.0f)));
    }
    glm::vec3 lightPos(0.0f, 3.0f, 3.0f);
    {
        // Light cube
        CMeshRenderer* pMeshRenderer = CMeshRenderer::Create();
        pMeshRenderer->SetMeshFilter(pCubeMeshFilter);
        pMeshRenderer->SetMaterial(pUnlitMaterial);
        CObject* pLightCubeObject = CObject::CreateObject("LightCube");
        pLightCubeObject->SetMeshRenderer(pMeshRenderer);
        pScene->AddObject(pLightCubeObject, CTransform::CreateTransform(lightPos, glm::vec3(0.0f), glm::vec3(0.20f)));
    }

    g_pCamera = CCamera::CreateCamera(width / (height * 1.0f), 60.0f, 0.1f, 100.0f);
    pScene->SetCamera(g_pCamera);

    SAttenuationDef def = {1.0f, 0.027f, 0.0028f};
    CPointLight* pPointLight = CPointLight::Create(lightPos, glm::vec3(1.0f, 1.0f, 1.0f), 0.1f, def);
    pScene->SetLight(pPointLight);

    while (!glfwWindowShouldClose(window))
    {
        // State Setting function
        glClearColor(0.0f, 0.3f, 0.2f, 1.0f);
        // State Using function
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float timeValue = (float)glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        float scale = (sin(timeValue)*2.0f);

        //pCubeTransform->SetPosition(glm::vec3(0.0f, scale, 0.0f));
        pCubeTransform->SetRotation(glm::vec3(timeValue*10.0f, timeValue*20.0f, 0.0f));

        pScene->Render(0, 0, width, height, scale);
        //Render(mainScene, 0, 0, width, height, scale);

        processInput(window);

        // Double buffering 
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    pPointLight->Destroy();
    g_pCamera->Destroy();
    pScene->Destroy();

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

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    g_fScale -= (float)yoffset*0.1f;
    if (g_fScale <= 0.0f)
        g_fScale = 0.01f;
    if (g_fScale > 5.0f)
        g_fScale = 5.0f;
}

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
    g_pCamera->SetDirection(glm::normalize(direction));
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
        g_pCamera->MoveForward(cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        g_pCamera->MoveForward(-cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        g_pCamera->MoveRight(-cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        g_pCamera->MoveRight(cameraSpeed);

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