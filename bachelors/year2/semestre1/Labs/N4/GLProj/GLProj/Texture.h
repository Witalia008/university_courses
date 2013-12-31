#pragma once
#include "Head.h"
#include "logging.h"

void flip_image(unsigned char *data, int x, int y) {
    int w_in_bytes = x * 4;
    for (int i = 0; i < (y >> 1); ++i)
        for (int j = 0; j < w_in_bytes; ++j)
            swap(data[i * w_in_bytes + j], data[(y - 1 - i) * w_in_bytes + j]);
}

unsigned int get_texture_obj(unsigned char *data, int x, int y, int pos) {
    unsigned int tex = 0;
    glGenTextures(1, &tex);
    glActiveTexture(GL_TEXTURE0 + pos);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA,
        x,
        y,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        data
    );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    return tex;
}

unsigned int load_texture(string filename, int pos) {
    int x, y, n;
    int force_channels = 4;
    unsigned char * image_data = stbi_load(filename.c_str(), &x, &y, &n, force_channels);
    if (!image_data) {
        gl_log("ERROR: loading texture from file " + filename + " failed", __FILE__, __LINE__);
        return -1;
    }
    gl_log("texture successfully loaded", __FILE__, __LINE__);
    if ((x & (x - 1)) != 0 || (y & (y - 1)) != 0)
        gl_log("WARNING: image has size not power of 2", __FILE__, __LINE__);
    flip_image(image_data, x, y);
    return get_texture_obj(image_data, x, y, pos);
}