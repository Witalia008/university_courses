#pragma once
#include "Head.h"

inline mat4 get_view_matr(float* cam_pos, float cam_yaw) {
    mat4 T = translate (identity_mat4 (), vec3 (-cam_pos[0], -cam_pos[1], -cam_pos[2]));
    mat4 R = rotate_y_deg (identity_mat4 (), -cam_yaw);
    mat4 view_mat = R * T;
    return view_mat;
}

float *get_camera_matr(int width, int height) {
#define ONE_DEG_IN_RAD (2.0 * M_PI) / 360.0; // 0.017444444
    // input variables
    float Near = 0.1f; // clipping plane
    float Far = 100.0f; // clipping plane
    float fov = 67.0f * ONE_DEG_IN_RAD; // convert 67 degrees to radians
    float aspect = (float)width / (float)height; // aspect ratio
    // matrix components
    float range = tan (fov * 0.5f) * Near;
    float Sx = (2.0f * Near) / (range * aspect + range * aspect);
    float Sy = Near / range;
    float Sz = -(Far + Near) / (Far - Near);
    float Pz = -(2.0f * Far * Near) / (Far - Near);
    float proj_mat[] = {
        Sx, 0.0f, 0.0f, 0.0f,
        0.0f, Sy, 0.0f, 0.0f,
        0.0f, 0.0f, Sz, -1.0f,
        0.0f, 0.0f, Pz, 0.0f
    };
    float *arr = new float[16];
    memcpy(arr, proj_mat, sizeof(proj_mat));
    return arr;
}