#include<iostream>
#include<GLFW\glfw3.h>

using namespace std;

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

    // TODO: Revisit once triangle is drawn
    //glViewport(0, 0, 800, 600);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Alpha Blend
    //glBlendFunc(GL_ONE, GL_ZERO); // Replace Blend
    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        // State Setting function
        glClearColor(0.0f, 0.3f, 0.2f, 1.0f);
        // State Using function
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Red Quad
        glBegin(GL_TRIANGLE_STRIP);
            glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
            
            glVertex3f(0.0f, 0.5f, 0.10f);  // 0
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

        // Double buffering 
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}