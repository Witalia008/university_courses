#pragma once
#include "Head.h"
#include "logging.h"

char* get_shader_from_file(string filename) {
    fstream in(filename, ios::in);
    if (!in.is_open()) {
        gl_log("Failed to load shader from file " + filename, __FILE__, __LINE__);
        return NULL;
    }
    string res = "";
    while (in.good()) {
        string x;
        getline(in, x);
        res += x + "\n";
    }
    gl_log("loaded shader from " + filename, __FILE__, __LINE__);
    in.close();
    char * ans = new char[res.length() + 1];
    strcpy(ans, res.c_str());
    return ans;
}

unsigned int register_vbo(float *a, int len) {
    if (len == 0) return 0;
    //vertex buffer object - unit for holding data on GPU
    unsigned int vbo = 0;
    //generate empty buffer
    glGenBuffers(1, &vbo);
    //set as current buffer of OpenGL's machine
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    //Copy all points to it
    glBufferData(GL_ARRAY_BUFFER, len * sizeof(float), a, GL_STATIC_DRAW);
    gl_log("created vertex buffer", __FILE__, __LINE__);
    return vbo;
}

unsigned int register_vao() {//vertex attribute object - holds information about all vertex buffers you want to use and their memory layouts
    unsigned int vao = 0;
    //vreate a new VAO
    glGenVertexArrays(1, &vao);
    //focus Gl machine onto it
    glBindVertexArray(vao);
    gl_log("created vertex attribute object", __FILE__, __LINE__);
    return vao;
}

void add_vbo_to_vao(unsigned vao, unsigned vbo, int pos, int n) {
    //bind VBO to VAO
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    //define a layout for first vertex buffer
    //it's attribute number 0, 3 - variables are made from every 3 points of GL_FLOAT type
    glVertexAttribPointer(pos, n, GL_FLOAT, GL_FALSE, 0, NULL);
    //enable one attribute for one buffer (vbo)
    glEnableVertexAttribArray(pos);
}

unsigned int create_shader(const char* code){
    //create vertex shader (initially empty)
    unsigned int shader = glCreateShader(GL_VERTEX_SHADER);
    //bind it with it's source
    glShaderSource(shader, 1, &code, NULL);
    //and compile
    //glCompileShader(shader);
    check_shader_compiled(shader);
    return shader;
}