#include"Shader.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include"glad/glad.h"
#include<GLFW\glfw3.h>

CShader* CShader::CreateShader(CShader::SHADER_TYPE type, const char* filePath)
{
    CShader* pShader = new CShader();
    if (!pShader->LoadPrivate(type, filePath))
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

bool CShader::LoadPrivate(CShader::SHADER_TYPE type, const char* filePath)
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

    std::ifstream inFile(filePath, std::ios::in);
    if (!inFile.is_open())
    {
        std::cout << "ERROR::SHADER::" << shaderType << "::LOADING_FAILED:: " << filePath << std::endl;
        glDeleteShader(m_idShader);
        return false;
    }

    std::string line;
    std::string shaderSource;
    while (std::getline(inFile, line))
    {
        shaderSource += line + "\n";
    }
    inFile.close();

    const char* shader = shaderSource.c_str();

    glShaderSource(m_idShader, 1, &shader, NULL);
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