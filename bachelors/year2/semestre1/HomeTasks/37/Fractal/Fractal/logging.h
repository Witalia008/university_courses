#pragma once
#include <string>
#include <iostream>
#include <chrono>
#include <fstream>
#include <GLFW\glfw3.h>

using namespace chrono;
using namespace std;

const string GL_LOG_FILE = "gl.log";

string toStr(int a) {
    char s[30];
    sprintf(s, "%d", a);
    return string(s);
}

bool restart_gl_log() {
    fstream out(GL_LOG_FILE, fstream::out);
    if (!out.is_open()) {
        cerr << "ERROR: could not open " << GL_LOG_FILE << " log file for writing" << endl;
        return false;
    }
    auto now = high_resolution_clock::to_time_t(high_resolution_clock::now());
    out << GL_LOG_FILE << " log. local time " << ctime(&now) << endl;
    out.close();
    return true;
}

bool gl_log(string message, string filename, int line) {
    fstream out(GL_LOG_FILE, fstream::out | fstream::app);
    if (!out.is_open()) {
        cerr << "ERROR: could not open " << GL_LOG_FILE << " log file for writing" << endl;
        return false;
    }
    out << filename << ":" << line << " " << message << endl;
    out.close();
    return true;
}

void glfw_error_callback(int error, const char * description) {
    cerr << "Error #" << error << ": " << description << endl;
    gl_log(description, __FILE__, __LINE__);
}

void _update_fps_counter(GLFWwindow* window) {
    static double previous_seconds = glfwGetTime ();
    static int frame_count;
    double current_seconds = glfwGetTime ();
    double elapsed_seconds = current_seconds - previous_seconds;
    if (elapsed_seconds > 0.25) {
        previous_seconds = current_seconds;
        double fps = (double)frame_count / elapsed_seconds;
        char tmp[128];
        sprintf (tmp, "opengl @ fps: %.2lf", fps);
        glfwSetWindowTitle (window, tmp);
        frame_count = 0;
    }
    frame_count++;
}

void _print_shader_info_log(unsigned int shader) {
    int max_length = 2048;
    int actual_length = 0;
    char log[2048];
    glGetShaderInfoLog(shader, max_length, &actual_length, log);
    gl_log("shader info log for GL index "+ toStr(shader) + ":\n" + string(log), __FILE__, __LINE__);
}

bool check_shader_compiled(unsigned int shader) {
    int params = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &params);
    if (GL_TRUE != params) {
        gl_log("shader index " + toStr(shader) + " compilation failed", __FILE__, __LINE__);
        _print_shader_info_log(shader);
        return false;
    } else {
        gl_log("shader index " + toStr(shader) + " compilation successful", __FILE__, __LINE__);
        return true;
    }
}

void _print_programme_info_log (unsigned int prog) {
    int max_length = 2048;
    int actual_length = 0;
    char log[2048];
    glGetProgramInfoLog (prog, max_length, &actual_length, log);
    gl_log("program info log for GL index " + toStr(prog) + ":\n" + string(log), __FILE__, __LINE__);
}

bool check_linking(unsigned int prog) {
    int params = GL_FALSE;
    glGetProgramiv(prog, GL_LINK_STATUS, &params);
    if (GL_TRUE != params) {
        gl_log("program index " + toStr(prog) + " failed to link", __FILE__, __LINE__);
        _print_programme_info_log(prog);
        return false;
    } else {
        gl_log("program index " + toStr(prog) + " linking successful", __FILE__, __LINE__);
        return true;
    }
}