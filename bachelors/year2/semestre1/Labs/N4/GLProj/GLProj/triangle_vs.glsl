#version 330

layout(location = 0) in vec3 inputPosition;
layout(location = 1) in vec4 vertex_colour;
layout(location = 2) in vec3 inputNormal;
layout(location = 3) in vec2 inputTexCoord;
layout(location = 4) in vec3 diffuseColor;
layout(location = 5) in vec3 specColor;
layout(location = 6) in vec3 ambColor;
layout(location = 7) in vec3 emmColor;

uniform mat4 rot;
uniform mat4 modelview, projection, normalMat;

varying vec4 forFragColor;

const vec3 lightPos = vec3(-2.0, 1.0, -3.0);
uniform int mode;

void main(){
  gl_Position = projection * modelview * rot * normalMat * vec4(inputPosition, 1.0);

  // all following gemetric computations are performed in the
  // camera coordinate system (aka eye coordinates)
  vec3 normal = vec3(normalMat * vec4(inputNormal, 0.0));
  vec4 vertPos4 = modelview * vec4(inputPosition, 1.0);
  vec3 vertPos = vec3(vertPos4) / vertPos4.w;
  vec3 lightDir = normalize(lightPos - vertPos);
  vec3 reflectDir = reflect(-lightDir, normal);
  vec3 viewDir = normalize(-vertPos);

  float lambertian = max(dot(lightDir,normal), 0.0);
  float specular = 0.0;
  
  if(lambertian > 0.0) {
    float specAngle = max(dot(reflectDir, viewDir), 0.0);
    specular = pow(specAngle, 4.0);

    // the exponent controls the shininess (try mode 2)
    if(mode == 2)  specular = pow(specAngle, 16.0);
       
    // according to the rendering equation we would need to multiply
    // with the the "lambertian", but this has little visual effect
    if(mode == 3) specular *= lambertian;
    // switch to mode 4 to turn off the specular component
    if(mode == 4) specular *= 0.0;
  }
  
  forFragColor = vec4(lambertian*diffuseColor + specular*specColor, 1.0);
}
