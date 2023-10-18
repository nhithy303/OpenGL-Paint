#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <fstream>
using namespace std;

string get_file_contents(string filename);

class Shader {
    GLuint ID;
public:
    Shader(string vertexFile, string fragmentFile);
    void Activate();
    void Delete();
};

#endif