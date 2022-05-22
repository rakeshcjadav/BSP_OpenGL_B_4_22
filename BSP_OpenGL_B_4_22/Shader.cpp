#include"Shader.h"
#include<iostream>
#include"glad/glad.h"
#include<GLFW\glfw3.h>

CShader* CShader::CreateShader(CShader::SHADER_TYPE type, const char* shaderSource)
{
    CShader* pShader = new CShader();
    if (!pShader->LoadPrivate(type, shaderSource))
    {
        pShader->Destroy();
        pShader = nullptr;
    }
    return pShader;
}

void CShader::Destroy()
{
    delete this;
}

/*
unsigned int CShader::GetID()
{

}*/

CShader::CShader()
{

}

CShader::~CShader()
{
    glDeleteShader(m_idShader);
}

bool CShader::LoadPrivate(CShader::SHADER_TYPE type, const char* shaderSource)
{
    std::string shaderType = "";
    if (type == SHADER_TYPE::VERTEX_SHADER)
    {
        shaderType = "VERTEX";
        m_idShader = glCreateShader(GL_VERTEX_SHADER);
    }
    else if (type == SHADER_TYPE::FRAGMENT_SHADER)
    {
        shaderType = "FRAGMENT";
        m_idShader = glCreateShader(GL_FRAGMENT_SHADER);
    }
    else
    {
        return false;
    }

    glShaderSource(m_idShader, 1, &shaderSource, NULL);
    glCompileShader(m_idShader);

    int  success;
    char infoLog[512];
    glGetShaderiv(m_idShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(m_idShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::"<<shaderType<<"::COMPILATION_FAILED\n" << infoLog << std::endl;
        glDeleteShader(m_idShader);
        return false;
    }
    return true;
}