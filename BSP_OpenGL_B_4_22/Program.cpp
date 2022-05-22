#include"Program.h"
#include"Shader.h"
#include<iostream>
#include"glad/glad.h"
#include<GLFW\glfw3.h>

CProgram* CProgram::CreateProgram(const char* VertexShaderSource, const char* FragmentShaderSource)
{
    CProgram* pProgram = new CProgram();
    if (!pProgram->LoadPrivate(VertexShaderSource, FragmentShaderSource))
    {
        pProgram->Destory();
        pProgram = nullptr;
    }
    return pProgram;
}

void CProgram::Destory()
{
    delete this;
}

void CProgram::Use()
{
    glUseProgram(m_idProgram);
}

void CProgram::SetUniformMatrix(const char* name, const glm::mat4& mat)
{
    glUniformMatrix4fv(glGetUniformLocation(m_idProgram, name), 1, false, glm::value_ptr(mat));
}

void CProgram::SetUniformFloat(const char* name, float fValue)
{
    glUniform1f(glGetUniformLocation(m_idProgram, name), fValue);
}

void CProgram::SetUniformInt(const char* name, int iValue)
{
    glUniform1i(glGetUniformLocation(m_idProgram, name), iValue);
}

void CProgram::SetUniformColor(const char* name, const glm::vec3& color)
{
    glUniform3fv(glGetUniformLocation(m_idProgram, name), 1, glm::value_ptr(color));
}

CProgram::CProgram()
{

}

CProgram::~CProgram()
{
    glDeleteProgram(m_idProgram);
}

bool CProgram::LoadPrivate(const char* VertexShaderSource, const char* FragmentShaderSource)
{
    CShader* pVertexShader = CShader::CreateShader(CShader::SHADER_TYPE::VERTEX_SHADER, VertexShaderSource);
    if (!pVertexShader)
        return false;
    CShader* pFragmentShader = CShader::CreateShader(CShader::SHADER_TYPE::FRAGMENT_SHADER, FragmentShaderSource);
    if (!pFragmentShader)
        return false;

    m_idProgram = glCreateProgram();
    glAttachShader(m_idProgram, pVertexShader->m_idShader);
    glAttachShader(m_idProgram, pFragmentShader->m_idShader);
    glLinkProgram(m_idProgram);

    int  success;
    char infoLog[512];
    glGetProgramiv(m_idProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(m_idProgram, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        return false;
    }

    pVertexShader->Destroy();
    pFragmentShader->Destroy();
    return true;
}