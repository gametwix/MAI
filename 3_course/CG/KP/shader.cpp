#include "headers/shader.h"
#include <cstring>

Shader::Shader(std::string VertexShaderFileName, std::string FragmentShaderFileName){
    LoadShader(VertexShaderFileName,FragmentShaderFileName);
}

void Shader::LoadShader(std::string VertexShaderFileName, std::string FragmentShaderFileName){
    std::string VertexShaderText;
    std::string FragmentShaderText;
    std::string buff;

    //Read file code VertexShader
    std::ifstream fin(VertexShaderFileName);
    if(!fin.is_open()){
        std::cout << "ERROR: Can't open vertex shader text file" << std::endl;
        return;
    }
    
    while(std::getline(fin,buff)){
        VertexShaderText.append('\n' + buff);
    }
    VertexShaderText.append("\n\0");
    fin.close();

    char* vertexShaderSource = new char[VertexShaderText.size()];
    memcpy(vertexShaderSource,VertexShaderText.data(),VertexShaderText.size()*sizeof(char));
    
    //Compile VertexShader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    GLint success;
    
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        std::cout << "ERROR: Vertex shader compilation failed" << std::endl;
        return;
    }
    
    
    //Read file code FragmentShader
    fin.open(FragmentShaderFileName);
    if(!fin.is_open()){
        std::cout << "ERROR: Can't open vertex shader text file" << std::endl;
        return;
    }
    while(std::getline(fin,buff)){
        FragmentShaderText.append('\n' + buff);
    }
    FragmentShaderText.append("\n\0");
    fin.close();
    
    char* fragmentShaderSource = new char[FragmentShaderText.size()+1];
    memcpy(fragmentShaderSource,FragmentShaderText.data(),(FragmentShaderText.size()+1)*sizeof(char));

    //Compile FragmentShader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        std::cout << "ERROR: Fragment shader compilation failed" << std::endl;
        return;
    }

    //Link shader program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        std::cout << "ERROR: Shader linking failed" << std::endl;
        return;
    }
}

void Shader::SetThisShader(){
    glUseProgram(shaderProgram);
}

GLuint Shader::GetShaderProgram(){return shaderProgram;}