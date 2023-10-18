#include "VAO.h"

VAO::VAO() {
    glGenVertexArrays(1, &ID);
}

void VAO::LinkAttrib(VBO &VBO, GLuint layout, GLuint size, GLenum type, GLenum normalized, GLsizeiptr stride, void* offset) {
    VBO.Bind();
    glVertexAttribPointer(layout, size, type, normalized, stride, offset);
    glEnableVertexAttribArray(layout);
    VBO.Unbind();
}

void VAO::Bind() {
    glBindVertexArray(ID);
}

void VAO::Unbind() {
    glBindVertexArray(0);
}

void VAO::Delete() {
    glDeleteVertexArrays(1, &ID);
}