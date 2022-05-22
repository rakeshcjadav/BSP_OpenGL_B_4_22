#pragma once

class CTexture
{
public:
    static CTexture* CreateTexture(const char* filePath);
    void Destroy();
    void Bind(unsigned int index);
protected:
    CTexture();
    ~CTexture();
    bool LoadPrivate(const char* filePath);
private:
    unsigned int m_idTexture;
};