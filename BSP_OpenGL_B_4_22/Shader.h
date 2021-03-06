#pragma once

class CProgram;

class CShader
{
    friend class CProgram;
public:
    enum class SHADER_TYPE {
        VERTEX_SHADER,
        FRAGMENT_SHADER
    };
public:
    static CShader* CreateShader(CShader::SHADER_TYPE type, const char* filePath);
    void Destroy();
    //unsigned int GetID();
protected:
    CShader();
    ~CShader();
    bool LoadPrivate(CShader::SHADER_TYPE type, const char* filePath);
private:
    unsigned int m_idShader;
};