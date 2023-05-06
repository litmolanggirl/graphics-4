#include <iostream>
#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#define STB_FAILURE_USERMSG
#include "STB/stb_image.h"

Texture::Texture(GLenum TextureTarget, const std::string& FileName) {
    m_textureTarget = TextureTarget;
    m_fileName = FileName;
    //m_fileName = "C:/Content/Sy7R1-X0MHs.png";
    //m_fileName = "C:/Content/test.png";
}

bool Texture::Load() {
    stbi_set_flip_vertically_on_load(1);
    int widht = 0, height = 0, bpp = 0;
    unsigned char* image_data = stbi_load(m_fileName.c_str(), &widht, &height, &bpp, 0);

    if (!image_data) {
        printf("Can't load texture from %s - %s\n", m_fileName.c_str(), stbi_failure_reason());
        exit(0);
    }
    printf("Widht %d, height %d, bpp %d\n", widht, height, bpp);

    glGenTextures(1, &m_textureObj);  // генерирует объект текстуры и помещает его в указатель на массив GLuint (второй параметр)
    glBindTexture(m_textureTarget, m_textureObj);  // сообщает OpenGL объект текстуры, который относится ко всем вызовам, связанным с текстурами, до тех пор, пока новый объект текстур не будет передан
    if (m_textureTarget == GL_TEXTURE_2D)
        // функция для загрузки главной части объекта текстуры (параметры: позиция, уровень детализации, внутренний формат, в котором OpenGL хранит текстуру, ширина и высота текстуры, рамка, формат, тип и адрес в памяти)
        glTexImage2D(m_textureTarget, 0, GL_RGB, widht, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data);
    else {
        printf("Support for texture target %x is not implemented\n", m_textureTarget);
        exit(1);
    }
    // указываем фильтры, которые будут использованы для увеличения и минимализации
    glTexParameterf(m_textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(m_textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(m_textureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(m_textureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glBindTexture(m_textureTarget, 0);

    return true;
}

void Texture::Bind(GLenum TextureUnit) {
    glActiveTexture(TextureUnit);
    glBindTexture(m_textureTarget, m_textureObj);  // привязываем объект текстур к модулю
}