#pragma once

#include <glad/glad.h>
#include <string>
#include <iostream>
#include <array>

#include "vendor/stb_image.h"

class Texture {
public:
    Texture(const std::string& path);

    uint32_t GetTexture() const { return m_TextureID; }

    void Bind()
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_TextureID);   
    }

    void UnBind()
    {
        glActiveTexture(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

private:
    uint32_t m_TextureID;
    static uint32_t m_nOfTextures;
};


