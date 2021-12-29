#include <iostream>
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

void get_object(std::vector<std::vector<float>> &points,std::vector<std::vector<int>> &faces,float a,float b,float h,int n, float A,float B,float D){
    points.clear();
    faces.clear();
    float m = 0;
    float t = 0;
    for(int i = 0; i < n; ++i){
        float x = a*b*glm::cos(t)/glm::sqrt(glm::pow(b,2)*glm::pow(cos(t),2) + glm::pow(a,2)*glm::pow(glm::sin(t),2));
        float y = a*b*glm::sin(t)/glm::sqrt(glm::pow(b,2)*glm::pow(cos(t),2) + glm::pow(a,2)*glm::pow(glm::sin(t),2));
        std::vector<float> point = {x,0.0f,y};
        points.push_back(point);
        if(A*x + B*y > m){
            m = A*x + B*y;
        }
        t += 2*3.1415926f/ n;
    }
    D += m;
    std::vector<int> top;
    std::vector<int> cut;
    std::vector<int> back(n);
    for(int i = 0; i < n; ++i){
        float x = a*b*glm::cos(t)/glm::sqrt(glm::pow(b,2)*glm::pow(cos(t),2) + glm::pow(a,2)*glm::pow(glm::sin(t),2));
        float y = a*b*glm::sin(t)/glm::sqrt(glm::pow(b,2)*glm::pow(cos(t),2) + glm::pow(a,2)*glm::pow(glm::sin(t),2));
        if(h <= D - A*x - B*y){
            std::vector<float> point = {x,h,y};
            points.push_back(point);
            top.push_back(i + n);
        }else{
            std::vector<float> point = {x,D - A*x - B*y,y};
            points.push_back(point);
            cut.push_back(i + n);
        }
        t += 2*3.1415926f/ n;
    }
    for(int i = 0; i < n; ++i){
        back[i] = n - i - 1;
    }
    faces.push_back(back);
    for(int i = 0; i < n; ++i){
        std::vector<int> face = {i,(i+1)%n,(i+1)%n + n,i + n};
        faces.push_back(face);
    }
    if(top.size() >= 3){
        faces.push_back(top);
    }
    if(cut.size() >= 3){
        int s = cut.size();
        for(int i = 0; i < s;++i){
            int j = (i + 1) % cut.size();
            if(glm::abs(cut[j] - cut[i]) > 1 && glm::abs(cut[j] - cut[i]) < n){
                int first = (cut[i] + 1) % n + n;
                int second = (cut[j] - 1) % n + n;
                cut.insert(cut.begin() + i+1,first);
                cut.insert(cut.begin() + i+2,second);
            }
        }
        faces.push_back(cut);
        
    }

    
}

int main()
{
    std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
    // Init GLFW
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


    std::vector<float> vertices = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };


    glm::vec4 light = glm::vec4(0.0f,10.0f,10.0f,1.0f);
    float lightpow = 1000.0f;
    std::vector<std::vector<float>> points;
    std::vector<std::vector<int>> faces;
    get_object(points,faces,0.5,0.5,0.5,120,1,1,0.2);
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
    Shader Gui_shader;
    Gui_shader.LoadShader("shaders/gui_vshader.glsl","shaders/gui_fshader.glsl");
    Slider slide1(window,Gui_shader,{WIDTH-230,HEIGHT-50},WIDTH,HEIGHT,200,30);
    Slider slide2(window,Gui_shader,{WIDTH-230,HEIGHT-90},WIDTH,HEIGHT,200,30);
    Slider slide3(window,Gui_shader,{WIDTH-230,HEIGHT-130},WIDTH,HEIGHT,200,30);
    Slider slide4(window,Gui_shader,{WIDTH-230,HEIGHT-170},WIDTH,HEIGHT,200,30);
    Slider slide5(window,Gui_shader,{WIDTH-230,HEIGHT-210},WIDTH,HEIGHT,200,30);
    Slider slide6(window,Gui_shader,{WIDTH-230,HEIGHT-250},WIDTH,HEIGHT,200,30);
    Slider slide7(window,Gui_shader,{WIDTH-230,HEIGHT-290},WIDTH,HEIGHT,200,30);

    double a = 0;
    double b = 0;
    double h = 0;
    int n = 0;
    double A = 0;
    double B = 0;
    double D = 0;
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
        
        cam.DrawObj(obj,sh,light,lightpow,currentFrame);
        //cam.DrawObj(ob2,sh,light,lightpow);
/*         sh.SetThisShader();
        obj.ConnectVAO(); 
        glDrawArrays(GL_TRIANGLES, 0, obj.GetNumVertex()*3);
        obj.DisconnectVAO(); */
        double an = slide1.CheckRes();
        double bn = slide2.CheckRes();
        double hn = slide3.CheckRes();
        double nn = int(slide4.CheckRes()*150) + 6;
        double An = (slide5.CheckRes()-0.5)*4;
        double Bn = (slide6.CheckRes()-0.5)*4;
        double Dn = slide7.CheckRes()*1.1;
        
        if(an != a || bn != b || hn != h || nn != n || An != A || Bn != B || Dn != D){
            a = an;
            b = bn;
            h = hn;
            n = nn;
            A = An;
            B = Bn;
            D = Dn;
            get_object(points,faces,a,b,h,n,A,B,D);
            obj.LoadObject(points,faces);
        }
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



