#include <iostream>
#include "texture.h"

Texture::Texture(GLenum TextureTarget, const std::string& FileName)
{
    m_textureTarget = TextureTarget;
    m_fileName = FileName;
    m_pImage = NULL;
}


bool Texture::Load()
{
    try {
        m_pImage = new Magick::Image(m_fileName); //This call loads the texture into memory, which is private and cannot be directly used by OpenGL.
        m_pImage->write(&m_blob, "RGBA"); //Then we write the image to a Magick::Blob object using RGBA format
    }
    catch (Magick::Error& Error) {
        std::cout << "Error loading texture '" << m_fileName << "': " << Error.what() << std::endl;
        return false;
    }

    glGenTextures(1, &m_textureObj); //generates the specified number of texture objects and places them in a pointer to a GLuint array
    glBindTexture(m_textureTarget, m_textureObj);//tells OpenGL the texture object that applies to all texture calls until a new texture object is passed
    glTexImage2D(m_textureTarget, 0, GL_RGB, m_pImage->columns(), m_pImage->rows(), -0.50, GL_RGBA, GL_UNSIGNED_BYTE, m_blob.data()); //function to load the main part of the texture object
    /*Here we specify the filters that will be used for zooming in and out*/
    glTexParameterf(m_textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(m_textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return true;
}

void Texture::Bind(GLenum TextureUnit)
{
    glActiveTexture(TextureUnit);
    glBindTexture(m_textureTarget, m_textureObj);
}