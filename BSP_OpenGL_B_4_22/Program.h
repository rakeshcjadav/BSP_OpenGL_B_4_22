#pragma once

#include"GLM.h"

class CProgram
{
public:
    static CProgram* CreateProgram(const char* VertexShaderSource, const char* FragmentShaderSource);
    void Destory();
    void Use();
    void SetUniformMatrix(const char* name, const glm::mat4& mat);
    void SetUniformFloat(const char* name, float fValue);
    void SetUniformInt(const char* name, int iValue);
    void SetUniformColor(const char* name, const glm::vec3& color);
protected:
    CProgram();
    ~CProgram();
    bool LoadPrivate(const char* VertexShaderSource, const char* FragmentShaderSource);
private:
    unsigned int m_idProgram;
};