#include "Head.h"

#include "logging.h"
#include "Models.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"

my_model model;

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

string dir = "models/dumbbell/";
string texts = "";
string modl = "dumbbell.ase";

float ang_x, ang_y, ang_z;

int main () {
    cin >> ang_x >> ang_y >> ang_z;
    restart_gl_log();
    load_mesh(dir + "/" + modl, 0.7, model);
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
    float matrix[] = {
        0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, -2.0f, -10.0f, 1.0f
    };
    float coord_l[] = {
        -1e5, 0, 0,
        1e5, 0, 0,
        0, -1e5, 0,
        0, 1e5, 0,
        0, 0, -1e5,
        0, 0, 1e5
    };
    /*float mtxp[] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, -2.0f, -2.0f, 1.0f
    };*/

    unsigned points_vbo = register_vbo(&model.vertices[0], model.vertices.size());
    unsigned colours_vbo = register_vbo(&model.colours[0], model.colours.size());
    unsigned normals_vbo = register_vbo(&model.normals[0], model.normals.size());
    unsigned textures_vbo = register_vbo(&model.textures[0], model.textures.size());
    unsigned diffuse_vbo = register_vbo(&model.diffuse[0], model.diffuse.size());
    unsigned spec_vbo = register_vbo(&model.specular[0], model.specular.size());
    unsigned amb_vbo = register_vbo(&model.ambient[0], model.ambient.size());
    unsigned emm_vbo = register_vbo(&model.emmisive[0], model.emmisive.size());

    unsigned vao = register_vao();
    add_vbo_to_vao(vao, points_vbo, 0, 3);
    add_vbo_to_vao(vao, colours_vbo, 1, 4);
    add_vbo_to_vao(vao, normals_vbo, 2, 3);
    add_vbo_to_vao(vao, textures_vbo, 3, 2);
    add_vbo_to_vao(vao, diffuse_vbo, 4, 3);
    add_vbo_to_vao(vao, spec_vbo, 5, 3);
    add_vbo_to_vao(vao, amb_vbo, 6, 3);
    add_vbo_to_vao(vao, emm_vbo, 7, 3);
    gl_log("created vertex attribute object", __FILE__, __LINE__);

    for (int i = 0; i < model.texs_name.size(); ++i) {
        /*string * fl = find(&model.texs_n[0], &model.texs_n[i], model.texs_n[i]);
        if (fl != &model.texs_n[i])
            model.texs.push_back(model.texs[fl - &model.texs_n[0]]);
        else*/
            model.texs.push_back(load_texture(dir + texts + model.texs_name[i], i));
    }

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
    glBindAttribLocation(shader_prog, 0, "inputPosition");
    glBindAttribLocation(shader_prog, 1, "vertex_colour");
    glBindAttribLocation(shader_prog, 2, "inputNormal");
    glBindAttribLocation(shader_prog, 3, "inputTexCoord");
    glBindAttribLocation(shader_prog, 4, "diffuseColor");
    glBindAttribLocation(shader_prog, 5, "specColor");
    glBindAttribLocation(shader_prog, 6, "ambColor");
    glBindAttribLocation(shader_prog, 7, "emmColor");
    glLinkProgram(shader_prog);
    check_linking(shader_prog);
    gl_log("shader program created", __FILE__, __LINE__);

    int matrix_location = glGetUniformLocation(shader_prog, "normalMat");
    gl_log("running program", __FILE__, __LINE__);

    float rot_ang = 5;
    float cam_speed = 2.0f;
    float cam_yaw_speed = 20.0f;
    float cam_pos[] = {0.0f, 0.0f, 10.0f};
    float cam_yaw = 0.0f; // y-rotation in degrees
    mat4 view_mat = get_view_matr(cam_pos, cam_yaw);
    float *proj_mat = get_camera_matr(vmode->width, vmode->height);

    int view_mat_location = glGetUniformLocation (shader_prog, "modelview");
    int proj_mat_location = glGetUniformLocation (shader_prog, "projection");
    int tex_loc = glGetUniformLocation(shader_prog, "basic_texture");
    int rot_loc = glGetUniformLocation(shader_prog, "rot");
    int mode_loc = glGetUniformLocation(shader_prog, "mode");
    model.starts.push_back(model.vertices.size());
    mat4 rot_n = rotate_x_deg(rotate_y_deg(rotate_z_deg(identity_mat4(), ang_z), ang_y), ang_x);
    mat4 rot_t = rotate_x_deg(rotate_y_deg(rotate_z_deg(identity_mat4(), -ang_z), -ang_y), -ang_x);
    mat4 rot_arr = identity_mat4();
    mat4 rt = rotate_z_deg(identity_mat4(), rot_ang);
    mat4 rot = rot_t * rot_arr * rot_n;
    while (!glfwWindowShouldClose(window)) {
        //add timer
        static float prev_time = glfwGetTime();
        float cur_time = glfwGetTime();
        float elapsed_seconds = cur_time - prev_time;
        if (elapsed_seconds > 0.005f) {
            rot_n = rotate_x_deg(rotate_y_deg(rotate_z_deg(identity_mat4(), ang_z), ang_y), ang_x);
            rot_t = rotate_x_deg(rotate_y_deg(rotate_z_deg(identity_mat4(), -ang_z), -ang_y), -ang_x);
            rt = rotate_z_deg(identity_mat4(), rot_ang);
            rot_arr = rot_arr * rt;
            prev_time = cur_time;
            rot = rot_t * rot_arr * rot_n;
        }

        _update_fps_counter(window);
        //wipe the drawing surface clear
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.6f, 0.6f, 0.8f, 1.0f);
        //glViewport(0, 0, vmode->width, vmode->height);
        
        glUseProgram(shader_prog);
        glBindVertexArray(vao);
        glUniformMatrix4fv(matrix_location, 1, GL_FALSE, matrix);
        glUniformMatrix4fv (view_mat_location, 1, GL_FALSE, view_mat.m);
        glUniformMatrix4fv (proj_mat_location, 1, GL_FALSE, proj_mat);
        glUniformMatrix4fv(rot_loc, 1, GL_FALSE, rot.m);
        glUniform1ui(mode_loc, 2);
        //draw points 0-3 from currently bound VAO with current in-use shader
        for (int i = 0; i + 1 < model.starts.size(); ++i) {
            if (model.tex_num.size()) glUniform1i(tex_loc, model.tex_num[i]);
            else glUniform1i(tex_loc, 0);
            glDrawArrays(GL_TRIANGLES, model.starts[i], model.starts[i + 1] - model.starts[i]);
        }
        //update other events like input hadling

        glfwPollEvents();
        //put the stuff we've been drawing onto the screen
        glfwSwapBuffers(window);
        //set escape key as close operation
        if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(window, 1);
        }
        // control keys
        bool cam_moved = false;
        if (glfwGetKey (window, GLFW_KEY_A)) {
            cam_pos[0] -= cam_speed * elapsed_seconds;
            cam_moved = true;
        }
        if (glfwGetKey (window, GLFW_KEY_D)) {
            cam_pos[0] += cam_speed * elapsed_seconds;
            cam_moved = true;
        }
        if (glfwGetKey (window, GLFW_KEY_PAGE_UP)) {
            cam_pos[1] += cam_speed * elapsed_seconds;
            cam_moved = true;
        }
        if (glfwGetKey (window, GLFW_KEY_PAGE_DOWN)) {
            cam_pos[1] -= cam_speed * elapsed_seconds;
            cam_moved = true;
        }
        if (glfwGetKey (window, GLFW_KEY_W)) {
            cam_pos[2] -= cam_speed * elapsed_seconds;
            cam_moved = true;
        }
        if (glfwGetKey (window, GLFW_KEY_S)) {
            cam_pos[2] += cam_speed * elapsed_seconds;
            cam_moved = true;
        }
        if (glfwGetKey (window, GLFW_KEY_LEFT)) {
            cam_yaw += cam_yaw_speed * elapsed_seconds;
            cam_moved = true;
        }
        if (glfwGetKey (window, GLFW_KEY_RIGHT)) {
            cam_yaw -= cam_yaw_speed * elapsed_seconds;
            cam_moved = true;
        }
        if (glfwGetKey (window, GLFW_KEY_KP_SUBTRACT) || glfwGetKey (window, GLFW_KEY_MINUS)) {
            rot_ang -= 0.1;
        }
        if (glfwGetKey (window, GLFW_KEY_KP_ADD) || glfwGetKey (window, GLFW_KEY_EQUAL)) {
            rot_ang += 0.1;
        }
        if (glfwGetKey (window, GLFW_KEY_KP_0)) {
            rot_ang = 0;
        }
        if (glfwGetKey (window, GLFW_KEY_KP_1)) {
            ang_x -= 1;
        }
        if (glfwGetKey (window, GLFW_KEY_KP_7)) {
            ang_x += 1;
        }
        if (glfwGetKey (window, GLFW_KEY_KP_2)) {
            ang_y -= 1;
        }
        if (glfwGetKey (window, GLFW_KEY_KP_8)) {
            ang_y += 1;
        }
        if (glfwGetKey (window, GLFW_KEY_KP_3)) {
            ang_z -= 1;
        }
        if (glfwGetKey (window, GLFW_KEY_KP_9)) {
            ang_z += 1;
        }
        if (glfwGetKey (window, GLFW_KEY_KP_4)) {
            ang_x = 0;
        }
        if (glfwGetKey (window, GLFW_KEY_KP_5)) {
            ang_y = 0;
        }
        if (glfwGetKey (window, GLFW_KEY_KP_6)) {
            ang_z = 0;
        }
        // update view matrix
        if (cam_moved) {
            view_mat = get_view_matr(cam_pos, cam_yaw);
            glUniformMatrix4fv (view_mat_location, 1, GL_FALSE, view_mat.m);
        }
    }

    // close GL context and any other GLFW resources
    glfwTerminate();
    gl_log("program exited successfully", __FILE__, __LINE__);
    return 0;
}