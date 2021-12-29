#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <sstream>
#include "headers/shader.h"
#include "headers/object.h"
#include "headers/camera.h"
#include "headers/gui.h"
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
#include <vector>
// GLFW
#include <GLFW/glfw3.h>


// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Window dimensions
const GLuint WIDTH = 1000, HEIGHT = 1000;

std::vector<bool> keys(1024,false);

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

void get_nurds_xy_4(float tt,std::vector<float> xlist,std::vector<float> ylist,std::vector<float> wlist,float &x,float &y){
    std::vector<float> t(xlist.size() + 4,0);
    for(int i = 0; i < xlist.size() - 4;++i){
        t[4+i] = i+1;
    }
    for(int i = 0; i < 4; ++i){
        t[xlist.size() + i] = xlist.size() - 3;
    }
    int d = 0;
    for(int i = 0; i < t.size() - 1; ++i){
        if(tt >= t[i] && tt < t[i+1]){
            d = i;
            break;
        }
    }
    std::vector<float> cx(4);
    std::vector<float> cy(4);
    std::vector<float> cw(4);
    for(int i = 0; i < 4; ++i){
        cx[i] = xlist[d-i]*wlist[d-i];
        cy[i] = ylist[d-i]*wlist[d-i];
        cw[i] = wlist[d-i];
    }
    for(int r = 4; r > 1; --r){
        int j = d;
        for(int s = 0; s < r-1;++s){
            float u_i = t[j];
            float u_ir = t[j+r-1];
            float omega = (tt - u_i)/(u_ir - u_i);
            cx[s] = omega*cx[s] + (1 - omega)*cx[s+1];
            cy[s] = omega*cy[s] + (1 - omega)*cy[s+1];
            cw[s] = omega*cw[s] + (1 - omega)*cw[s+1];
            j = j-1;
        }
    }
    x = cx[0]/cw[0];
    y = cy[0]/cw[0];
}

void get_object(std::vector<std::vector<float>> &points,std::vector<std::vector<int>> &faces){
    std::ifstream fin("figure");
    std::string buff;
    int kt = 0,kn = 0;
    std::vector<float> xlist;
    std::vector<float> ylist;
    std::vector<float> wlist;
    while(std::getline(fin,buff)){
        std::stringstream linestream(buff);
        if(kt == 0 && kn == 0){
            linestream >> kt >> kn;
        }else{
            float x,y,w;
            linestream >> x >> y >> w;
            xlist.push_back(x);
            ylist.push_back(y);
            wlist.push_back(w);
        }
    }
    std::cout << kt << std::endl;
    for(float tt = 0; tt < xlist.size() - 3; tt+=((float)xlist.size() - 3.0f)/kt){
        float x,y;
        get_nurds_xy_4(tt,xlist,ylist,wlist,x,y);
        std::vector<float> point(3);
        point[0] = x;
        point[1] = y;
        point[2] = 0;

        points.push_back(point);
    }
    kt = points.size();
    int n= 1 ;
    for(float t = 2*3.141592/(float)kn; t < 2*3.141592;t+= 2*3.141592/(float)kn){
        ++n;
        std::cout << t << std::endl;
        glm::mat4 rotate = glm::rotate(glm::mat4(1.0),t, glm::vec3(0.0f,1.0f,0.0f));
        for(int k = 0; k < kt;++k){
            glm::vec4 point(points[k][0],points[k][1],points[k][2],1.0f);
            point = rotate*point;
            std::vector<float> pp = {point[0],point[1],point[2]};
            points.push_back(pp);
        }
    }
    kn = n;
    for(int i = 0; i < kn;++i){
        for(int j = 0; j < kt - 1; ++j){
            std::vector<int> face(4);
            face[0] = i*kt + j;
            face[1] = ((i+1)*kt)%(kn*kt) + j;
            face[2] = ((i+1)*kt)%(kn*kt) + j + 1;
            face[3] = i*kt + j + 1;
            faces.push_back(face);
        }
    }
    for(auto &point: points){
        std::cout << point[0] << " " << point[1] << " " << point[2] << std::endl;
    }

    for(auto &face: faces){
        std::cout << face[0] << " " << face[1] << " " << face[2]<<  " " << face[3] << std::endl;
    }
}

int main()
{
    std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
    // Init GLFWlight
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    // Set the required callback functions
    glfwSetKeyCallback(window, key_callback);

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    glewInit();

    // Define the viewport dimensions
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);  
    glViewport(0, 0, width, height);


    Shader sh;
    sh.LoadShader("shaders/vshader.glsl","shaders/fshader.glsl");


    glm::vec4 light = glm::vec4(0.0f,30.0f,0.0f,1.0f);
    float lightpow = 10000.0f;
    std::vector<std::vector<float>> points;
    std::vector<std::vector<int>> faces;
    get_object(points,faces);
    Object obj;
    obj.LoadObject(points,faces);
    //ob2.LoadObject(vertices);
    glm::mat4 trans(1.0f);
    //ob2.SetModel( glm::translate(trans, glm::vec3(0.0f, 0.0f, -10.0f)));
    //obj.LoadObject(vertexes);
    // Game loop
    Camera cam(WIDTH,HEIGHT);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);


    double a = 0;
    double b = 0;
    double h = 0;
    int n = 0;
    double A = 0;
    double B = 0;
    double D = 0;
    double strenght = 0;
    double size = 1;
    while (!glfwWindowShouldClose(window))
    {
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        //light = glm::rotate(glm::mat4(1.0f),glm::radians(deltaTime*30),glm::vec3(0.0f,1.0f,0.0f))*light;
        //light = glm::rotate(glm::mat4(1.0f),glm::radians(deltaTime*20),glm::vec3(1.0f,0.0f,0.0f))*light;
        //light = glm::rotate(glm::mat4(1.0f),glm::radians(deltaTime*20),glm::vec3(0.0f,0.0f,1.0f))*light;
        glfwPollEvents();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cam.Control(keys,deltaTime);
        
        cam.DrawObj(obj,sh,light,lightpow,currentFrame,strenght,size);
        //cam.DrawObj(ob2,sh,light,lightpow);
/*         sh.SetThisShader();
        obj.ConnectVAO(); 
        glDrawArrays(GL_TRIANGLES, 0, obj.GetNumVertex()*3);
        obj.DisconnectVAO(); */
        //slide.Draw();
        glfwSwapBuffers(window);
    }

    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if(key > 0 && key < 1024){
        if(action == GLFW_PRESS)
            keys[key] = true;
        else if(action == GLFW_RELEASE)
            keys[key] = false;	
    }
}



