#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "vendor/stb_image.h"

#include <string>
#include <iostream>
#include <array>

class Texture {
public:
    Texture() { currentTexture = -1; }

    void Bind()
    {
        for(int i = 0; i < textureIDs.size(); i++) {
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, textureIDs[i]);
        }
    }

    void unBind()
    {
        for(int i = 0; i < textureIDs.size(); i++) {
            glActiveTexture(0);
            glBindTexture(0, textureIDs[i]);
        }
    }

    void addTexture(const std::string& path, GLenum texStyle = GL_LINEAR) 
    {
        currentTexture++;
        
        glGenTextures(1, &textureIDs[currentTexture]);
        glBindTexture(GL_TEXTURE_2D, textureIDs[currentTexture]);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texStyle);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texStyle);

        int width, height, nrChannels;
        unsigned char* data;

        stbi_set_flip_vertically_on_load(true);

        data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

        if(!data) 
        {
            std::cout << "Error loading: " << path << std::endl;
            return;
        }
        
        if(path.find("jpg") != std::string::npos)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        else if (path.find("png") != std::string::npos)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE0 + currentTexture, textureIDs[currentTexture]);

        stbi_image_free(data);
    }

public:
    std::array<unsigned int, 16> textureIDs;
private:
    int currentTexture;
};


