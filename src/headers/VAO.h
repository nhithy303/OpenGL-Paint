#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>
#include "VBO.h"

class VAO {
    GLuint ID;
public:
    VAO();
    void LinkAttrib(VBO &VBO, GLuint layout, GLuint size, GLenum type, GLenum normalized, GLsizeiptr stride, void* offset);
    void Bind();
    void Unbind();
    void Delete();
};

#endif