#include "headers/gui.h"

Slider::Slider(GLFWwindow* window,Shader sh,std::pair<int,int> pos,float width,float height,float size_w, float size_h) : 
    Window(window), Pos(pos), Width_screen(width),Height_screen(height),Size_w(size_w),Size_h(size_h){
        std::vector<float> fr = {-width/2,-height/2 + size_h/2 - 2,0.5f,0.0f,0.0f,0.0f,
                                -width/2+size_w,-height/2 + size_h/2 - 2,0.5f,0.0f,0.0f,0.0f,
                                -width/2,-height/2 + size_h/2 + 2,0.5f,0.0f,0.0f,0.0f,
                                -width/2,-height/2 + size_h/2 + 2,0.5f,0.0f,0.0f,0.0f,
                                -width/2+size_w,-height/2 + size_h/2 + 2,0.5f,0.0f,0.0f,0.0f,
                                -width/2+size_w,-height/2 + size_h/2 - 2,0.5f,0.0f,0.0f,0.0f,};
        
        std::vector<float> s = {-width/2+PSl,-height/2 ,0.5f,1.0f,0.0f,0.0f,
                                -width/2+10+PSl,-height/2 ,0.5f,1.0f,0.0f,0.0f,
                                -width/2+PSl,-height/2 + size_h,0.5f,1.0f,0.0f,0.0f,
                                -width/2+PSl,-height/2 + size_h,0.5f,1.0f,0.0f,0.0f,
                                -width/2+10+PSl,-height/2 + size_h,0.5f,1.0f,0.0f,0.0f,
                                -width/2+10+PSl,-height/2 ,0.5f,1.0f,0.0f,0.0f,};
        Frame.LoadObject(fr);
        Sl.LoadObject(s);
        for(int i = 0; i < 36;++i){
            std::cout << fr[i] << " ";
        }
        std::cout << std::endl;
        shader = sh;
        orthmat = glm::ortho(-width,width, -height, height, 0.01f, 10.0f );
        for(int i = 0; i < 16;++i){
            std::cout << orthmat[i/4][i%4] << " ";
        }
        std::cout << std::endl;
    }

void Slider::Draw(){
    GLuint shaderProgram = shader.GetShaderProgram();
    shader.SetThisShader();
    glClear(GL_DEPTH_BUFFER_BIT);
    GLuint orthmatLoc = glGetUniformLocation(shaderProgram, "ProjectionMat");
    glUniformMatrix4fv(orthmatLoc, 1, GL_FALSE, glm::value_ptr(orthmat));
    GLuint posLoc = glGetUniformLocation(shaderProgram, "PosSl");
    glUniform2f(posLoc, Pos.first,Pos.second);
    Frame.ConnectVAO();
    glDrawArrays(GL_TRIANGLES, 0,Frame.GetNumVertex());
    
    Frame.DisconnectVAO();
    glClear(GL_DEPTH_BUFFER_BIT);
    Sl.ConnectVAO();
    glDrawArrays(GL_TRIANGLES, 0,Sl.GetNumVertex());
    Sl.DisconnectVAO();
    glUseProgram(0);
}

float Slider::CheckRes(){
    double x,y;
    glfwGetCursorPos(Window,&x,&y);
    if(glfwGetMouseButton(Window,GLFW_MOUSE_BUTTON_1) == GLFW_PRESS && x >= Pos.first && x <= Pos.first+Size_w-10 && Height_screen - y >= Pos.second && Height_screen - y <= Pos.second+Size_h){
        PSl = x - Pos.first;
        std::vector<float> s = {-Width_screen/2+PSl,-Height_screen/2 ,0.5f,1.0f,0.0f,0.0f,
                                    -Width_screen/2+10+PSl,-Height_screen/2 ,0.5f,1.0f,0.0f,0.0f,
                                    -Width_screen/2+PSl,-Height_screen/2 + Size_h,0.5f,1.0f,0.0f,0.0f,
                                    -Width_screen/2+PSl,-Height_screen/2 + Size_h,0.5f,1.0f,0.0f,0.0f,
                                    -Width_screen/2+10+PSl,-Height_screen/2 + Size_h,0.5f,1.0f,0.0f,0.0f,
                                    -Width_screen/2+10+PSl,-Height_screen/2 ,0.5f,1.0f,0.0f,0.0f,};
        Sl.LoadObject(s);
    }
    this->Draw();
    return PSl / Size_w;
}