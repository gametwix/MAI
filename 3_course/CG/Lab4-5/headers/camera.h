#pragma once
#include "shader.h"
#include "object.h"
#include "../glm/glm.hpp"
#include "../glm/gtc/type_ptr.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>


class Camera{
    private:
        GLfloat MovementSpeed = 2;
        GLfloat RotationSpeed = 50;

        //Position
        glm::vec3 CameraPos = glm::vec3(0.0f,0.0f,-0.3f);
        glm::vec3 CameraFront = glm::vec3(0.0f,0.0f,1.0f);
        glm::vec3 CameraUp = glm::vec3(0.0f,1.0f,0.0f);
        glm::vec3 CameraRight = glm::vec3(1.0f,0.0f,0.0f);

        GLfloat Yaw;
        GLfloat Pitch;

        glm::mat4 ViewMatrix;

        //Projection
        GLfloat Width;
        GLfloat Height;
        GLfloat Fov = 45.0f;
        GLfloat Near = 0.1f;
        GLfloat Far = 1000.0f;
        
        glm::mat4 ProjectionMatrix;

        void GenViewMatrix();
        void GenProjectionMatrix();
        

    public:
        Camera(GLfloat width, GLfloat height,glm::vec3 camerapos = glm::vec3(0.0f,0.0f,-3.0f),GLfloat yaw = 0, GLfloat pitch = 0);
        void DrawObj(Object &obj, Shader &shader, glm::vec4 light, float lightpow,float time,float streght, float size);
        void Control(std::vector<bool> &keys, GLfloat deltaTime);
};

