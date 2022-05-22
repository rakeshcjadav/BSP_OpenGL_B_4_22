#include"Texture.h"
#include<iostream>
#include"glad/glad.h"
#include<GLFW\glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"

CTexture* CTexture::CreateTexture(const char* filePath)
{
    CTexture* pTexture = new CTexture();
    if (!pTexture->LoadPrivate(filePath))
    {
        pTexture->Destroy();
        pTexture = nullptr;
    }
    return pTexture;
}

void CTexture::Destroy()
{
    delete this;
}

void CTexture::Bind(unsigned int index)
{
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, m_idTexture);
}

CTexture::CTexture()
{

}

CTexture::~CTexture()
{
    glDeleteTextures(1, &m_idTexture);
}

bool CTexture::LoadPrivate(const char* filePath)
{
    stbi_set_flip_vertically_on_load(true);
    int width, height, nrChannels;
    unsigned char* data = stbi_load(filePath, &width, &height, &nrChannels, 0);

    if (data)
    {
        std::cout << "Image Loaded : " << width << ", " << height << ", Channels : " << nrChannels << std::endl;
    }
    else
    {
        std::cout << "Could not load image" << std::endl;
        return false;
    }

    GLenum format = GL_RGB;
    if (nrChannels == 3)
        format = GL_RGB;
    else if (nrChannels == 4)
        format = GL_RGBA;

    glGenTextures(1, &m_idTexture);
    glBindTexture(GL_TEXTURE_2D, m_idTexture);
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

    if (data)
        stbi_image_free(data);

    return true;
}