attribute vec2 vertexPosition;
uniform mat4 perspectiveMatrix;

void main(void) {
    gl_Position = /*perspectiveMatrix * */vec4(vertexPosition, 0.0, 1.0);
}