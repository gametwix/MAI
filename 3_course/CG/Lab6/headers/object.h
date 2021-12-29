#pragma once
#include "../glm/glm.hpp"
#include "../glm/gtc/type_ptr.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>

class Object{
    private:
        GLfloat vertices[100000];
        GLuint VAO,VBO;
        uint64_t num_vertex = 0;
        glm::mat4 model = glm::mat4(1.0);

        void Triangulation(std::vector<std::vector<float>> polygon,std::vector<float> normal, std::vector<std::vector<float>> &ans);

    public:
        Object(){};
        ~Object();
        Object(std::vector<GLfloat> &vertexes);
        void LoadObject(std::vector<GLfloat> &vertexes);
        void LoadObject(std::vector<std::vector<float>> points,std::vector<std::vector<int>> faces);
        void ConnectVAO();
        void DisconnectVAO();
        uint64_t GetNumVertex();
        void SetModel(glm::mat4 nm);
        glm::mat4 GetModelMatrix();
};