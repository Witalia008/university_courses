#include <GL\glew.h> // include GLEW and new version of GL on Windows
#define GLFW_DLL
#include <GLFW\glfw3.h> // GLFW helper library
#include <stdio.h>
#include <Windows.h>
#include <cassert>
#include <string>
#include <sstream>
#include <memory>

using namespace std;

#include "logging.h"
#include "fractals.h"

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

/**
* vertex shader souce.
* vertex shader is responsible for drawing vertices
*/
const char* vertex_shader;
/**
* fragment shader source.
* fragment shader is responsible for colouring pixels
*/
const char* fragment_shader;
Fractal fractal("fractal.txt");

int main () {
    pair<float*, int> cc = fractal.get_points(pt(0, 0));
    float *points = cc.first;
    restart_gl_log();
    vertex_shader = const_cast<const char*>(get_shader_from_file("triangle_vs.glsl"));
    fragment_shader = const_cast<const char*>(get_shader_from_file("triangle_fs.glsl"));
    glfwWindowHint(GLEW_VERSION_MINOR, 3);
    //make not support old functions, that were marked as "to remove"
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //make lines look smoother
    glfwWindowHint (GLFW_SAMPLES, 6);
    assert(gl_log(string("starting GLFW ") + glfwGetVersionString(), __FILE__, __LINE__));
    glfwSetErrorCallback(glfw_error_callback);
    // start GL context and O/S window using the GLFW helper library
    if (!glfwInit ()) {
        //gl_log("GLFW3 Initialization failed", __FILE__, __LINE__);
        return 1;
    }
    gl_log("GLFW3 Initialization succeed", __FILE__, __LINE__);

    //in fullscreen mode
    GLFWmonitor* mon = glfwGetPrimaryMonitor();
    const GLFWvidmode* vmode = glfwGetVideoMode(mon);
    GLFWwindow* window = glfwCreateWindow (
        vmode->width, vmode->height, "GL Program", mon, NULL
        );
    if (!window) {
        //gl_log("could not open window with GLFW3", __FILE__, __LINE__);
        glfwTerminate();
        return 1;
    }
    gl_log("successfully created window using GLFW3", __FILE__, __LINE__);
    glfwMakeContextCurrent (window);

    // start GLEW extension handler
    glewInit ();
    
    // get version info
    const GLubyte* renderer = glGetString (GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString (GL_VERSION); // version as a string
    cout << "Renderer " << renderer << endl;
    cout << "OpenGL version supported " << version << endl;

    // tell GL to only draw onto a pixel if the shape is closer to the viewer
    glEnable (GL_DEPTH_TEST); // enable depth-testing
    glDepthFunc (GL_LESS); // depth-testing interprets a smaller value as "closer"

    /* OTHER STUFF GOES HERE NEXT */

    //vertex buffer object - unit for holding data on GPU
    unsigned int points_vbo = 0;
    //generate empty buffer
    glGenBuffers(1, &points_vbo);
    //set as current buffer of OpenGL's machine
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    //Copy all points to it
    glBufferData(GL_ARRAY_BUFFER, cc.second * sizeof(float), points, GL_STATIC_DRAW);
    gl_log("created vertex buffer", __FILE__, __LINE__);

    //vertex attribute object - holds information about all vertex buffers you want to use and their memory layouts
    unsigned int vao = 0;
    //vreate a new VAO
    glGenVertexArrays(1, &vao);
    //focus Gl machine onto it
    glBindVertexArray(vao);
    //bind VBO to VAO
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    //define a layout for first vertex buffer
    //it's attribute number 0, 3 - variables are made from every 3 points of GL_FLOAT type
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    //enable one attribute for one buffer (vbo)
    glEnableVertexAttribArray(0);
    gl_log("created vertex attribute object", __FILE__, __LINE__);

    //create vertex shader (initially empty)
    unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
    //bind it with it's source
    glShaderSource(vs, 1, &vertex_shader, NULL);
    //and compile
    glCompileShader(vs);
    check_shader_compiled(vs);
    unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);
    check_shader_compiled(fs);
    gl_log("shaders compiled successfully", __FILE__, __LINE__);

    //create shader program
    unsigned int shader_prog = glCreateProgram();
    //attach vertex and fragment shaders and link program
    glAttachShader(shader_prog, vs);
    glAttachShader(shader_prog, fs);
    glLinkProgram(shader_prog);
    check_linking(shader_prog);
    gl_log("shader program created", __FILE__, __LINE__);

    gl_log("running program", __FILE__, __LINE__);

    while (!glfwWindowShouldClose(window)) {
        _update_fps_counter(window);
        //wipe the drawing surface clear
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.6f, 0.6f, 0.8f, 1.0f);
        glViewport(0, 0, vmode->width, vmode->height);
        
        glUseProgram(shader_prog);
        glBindVertexArray(vao);
        //draw points 0-3 from currently bound VAO with current in-use shader
        glDrawArrays(GL_LINES, 0, cc.second / 3);
        //update other events like input hadling

        glfwPollEvents();
        //put the stuff we've been drawing onto the screen
        glfwSwapBuffers(window);
        //set escape key as close operation
        if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(window, 1);
        }
    }

    // close GL context and any other GLFW resources
    glfwTerminate();
    gl_log("program exited successfully", __FILE__, __LINE__);
    return 0;
}