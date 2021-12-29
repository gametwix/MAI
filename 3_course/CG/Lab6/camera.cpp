#include "headers/camera.h"
#include <iostream>

void Camera::GenProjectionMatrix(){
    //ProjectionMatrix = glm::perspective(Fov,Width/Height,Near,Far);
    ProjectionMatrix =glm::ortho(-1.0f,1.0f, -1.0f, 1.0f, 0.01f, 10.0f );
}

Camera::Camera(GLfloat width, GLfloat height,glm::vec3 camerapos,GLfloat yaw, GLfloat pitch) :
Yaw(yaw), Pitch(pitch), CameraPos(camerapos), Width(width), Height(height) {
    GenViewMatrix();
    GenProjectionMatrix();
}

void Camera::DrawObj(Object &obj, Shader &shader, glm::vec4 light, float lightpow,float time){
    shader.SetThisShader();
    glm::mat4 modelMatrix = obj.GetModelMatrix();
    //Set Matrixs
    GLuint shaderProgram = shader.GetShaderProgram();

    GLuint modelLoc = glGetUniformLocation(shaderProgram, "modelMatrix");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    GLuint viewLoc = glGetUniformLocation(shaderProgram, "viewMatrix");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(ViewMatrix));

    GLuint projectionLoc = glGetUniformLocation(shaderProgram, "projectionMatrix");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(ProjectionMatrix));

    //std::cout << light[0] << " " << light[1] << " " << light[2] << std::endl;

    GLuint lightPosLoc = glGetUniformLocation(shaderProgram, "lightPos");
    glUniform3f(lightPosLoc,light[0],light[1],light[2]);

    GLuint lightPowLoc = glGetUniformLocation(shaderProgram, "lightPow");
    glUniform1f(lightPowLoc, lightpow);

    GLuint timeLoc = glGetUniformLocation(shaderProgram, "Time");
    glUniform1f(timeLoc, time);

    GLint viewPosLoc = glGetUniformLocation(shaderProgram, "viewPos");
    glUniform3f(viewPosLoc, CameraPos.x, CameraPos.y, CameraPos.z);

    //Draw
    shader.SetThisShader();
    obj.ConnectVAO();
    glDrawArrays(GL_TRIANGLES, 0,obj.GetNumVertex());
    obj.DisconnectVAO();
    glUseProgram(0);

}

void Camera::GenViewMatrix(){
    ViewMatrix = glm::lookAt(CameraPos,CameraPos+CameraFront,CameraUp);
}

void Camera::Control(std::vector<bool> &keys, GLfloat deltaTime){
    GLfloat DeltaS= MovementSpeed * deltaTime;
    if(keys[GLFW_KEY_W]){
        CameraPos += CameraFront*DeltaS;
        GenViewMatrix();
    }
    if(keys[GLFW_KEY_S]){
        CameraPos -= CameraFront*DeltaS;
        GenViewMatrix();
    }
    if(keys[GLFW_KEY_D]){
        CameraPos -= CameraRight*DeltaS;
        GenViewMatrix();
    }
    if(keys[GLFW_KEY_A]){
        CameraPos += CameraRight*DeltaS;
        GenViewMatrix();
    }
    if(keys[GLFW_KEY_SPACE]){
        CameraPos += CameraUp*DeltaS;
        GenViewMatrix();
    }
    if(keys[GLFW_KEY_LEFT_SHIFT ]){
        CameraPos -= CameraUp*DeltaS;
        GenViewMatrix();
    }
    if(keys[GLFW_KEY_RIGHT]){ 
        glm::mat4 rotate4 = glm::rotate(glm::mat4(1.0),glm::radians(-RotationSpeed * deltaTime), CameraUp);
        glm::mat3 rotate3;
        for(int i = 0; i< 3; i++){
            for(int j = 0; j< 3; j++){
                rotate3[i][j] = rotate4[i][j];
            }
        }
        CameraFront = rotate3*CameraFront;
        CameraRight = rotate3*CameraRight;
        CameraUp = rotate3*CameraUp;
        GenViewMatrix();
    }
    if(keys[GLFW_KEY_LEFT]){
        glm::mat4 rotate4 = glm::rotate(glm::mat4(1.0),glm::radians(RotationSpeed * deltaTime), CameraUp);
        glm::mat3 rotate3;
        for(int i = 0; i< 3; i++){
            for(int j = 0; j< 3; j++){
                rotate3[i][j] = rotate4[i][j];
            }
        }
        CameraFront = rotate3*CameraFront;
        CameraRight = rotate3*CameraRight;
        CameraUp = rotate3*CameraUp;
        GenViewMatrix();
        GenViewMatrix();
    }
    if(keys[GLFW_KEY_UP]){
        glm::mat4 rotate4 = glm::rotate(glm::mat4(1.0),glm::radians(-RotationSpeed * deltaTime), CameraRight);
        glm::mat3 rotate3;
        for(int i = 0; i< 3; i++){
            for(int j = 0; j< 3; j++){
                rotate3[i][j] = rotate4[i][j];
            }
        }
        CameraFront = rotate3*CameraFront;
        CameraRight = rotate3*CameraRight;
        CameraUp = rotate3*CameraUp;
        GenViewMatrix();
    }
    if(keys[GLFW_KEY_DOWN]){
        glm::mat4 rotate4 = glm::rotate(glm::mat4(1.0),glm::radians(RotationSpeed * deltaTime), CameraRight);
        glm::mat3 rotate3;
        for(int i = 0; i< 3; i++){
            for(int j = 0; j< 3; j++){
                rotate3[i][j] = rotate4[i][j];
            }
        }
        CameraFront = rotate3*CameraFront;
        CameraRight = rotate3*CameraRight;
        CameraUp = rotate3*CameraUp;
        GenViewMatrix();
    }
}