#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <iostream>

class Shader{
    private:
        GLuint vertexShader;
        GLuint fragmentShader;
        GLuint shaderProgram;
    public:

        Shader(){};
        Shader(std::string VertexShaderFileName, std::string FragmentShaderFileName);
        void LoadShader(std::string VertexShaderFileName, std::string FragmentShaderFileName);
        void SetThisShader();
        GLuint GetShaderProgram();
};