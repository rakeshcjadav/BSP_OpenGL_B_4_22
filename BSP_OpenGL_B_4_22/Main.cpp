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

    while (!glfwWindowShouldClose(window))
    {
        // State Setting function
        glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
        // State Using function
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);

        // State setting fucntion
        glBegin(GL_TRIANGLES);
            glColor3f(0.0f, 0.0f, 1.0f);
            glVertex3f(-0.5f, 0.1f, -0.05f);
            glVertex3f(0.5f, 0.1f, -0.05f);
            glVertex3f(0.0f, -0.5f, -0.05f);
        glEnd();

        glBegin(GL_TRIANGLES);
            glColor4f(1.0f, 0.0f, 0.0f, 0.1f);
            glVertex3f(-0.5f, 0.0f, -0.10f);
            glVertex3f(0.5f, 0.0f, -0.10f);
            glVertex3f(0.0f, 0.5f, -0.10f);
        glEnd();

        // Double buffering 
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}