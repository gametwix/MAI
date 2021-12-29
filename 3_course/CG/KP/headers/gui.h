#pragma once
#include "../glm/glm.hpp"
#include "../glm/gtc/type_ptr.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include "object.h"
#include "shader.h"

class Slider{
    private:
        GLFWwindow* Window;
        Object Frame;
        Object Sl;
        std::pair<int,int> Pos;
        float Width_screen;
        float Height_screen;
        float Size_w;
        float Size_h;
        float PSl = 0;
        glm::mat4 orthmat;
        Shader shader;


    public:
        Slider(GLFWwindow* window,Shader sh,std::pair<int,int> pos,float width,float height,float size_w, float size_h);
        void Draw();
        float CheckRes();
};