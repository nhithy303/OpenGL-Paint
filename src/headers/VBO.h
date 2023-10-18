#ifndef VBO_H
#define VBO_H

#include <glad/glad.h>

class VBO {
    GLuint ID;
public:
    VBO(GLfloat* vertices, GLsizeiptr size);
    void Bind();
    void Unbind();
    void Delete();
};

#endif