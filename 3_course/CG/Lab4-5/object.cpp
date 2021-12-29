#include "headers/object.h"
#include <cstring>
#include <iostream>
#include <sstream>
#include <fstream>




bool Ray_crosses(std::vector<float> c, std::vector<float> a,std::vector<float> b){
    std::vector<float> d(2);
    d[0] = c[0] + 1;
    d[1] = c[1];
    /* std::cout<< "d c a b "<< std::endl; 
    std::cout << d[0]<< " " <<d[1]<< std::endl;
    std::cout << c[0]<< " " <<c[1]<< std::endl;
    std::cout << a[0]<< " " <<a[1]<< std::endl;
    std::cout << b[0]<< " " <<b[1]<< std::endl; */
    float s = ((a[0] - c[0])*(d[1]-c[1]) - (d[0]-c[0])*(a[1] - c[1]))/((d[0] - c[0])*(b[1] - a[1]) - (b[0] - a[0])*(d[1]-c[1]));
    float r = ((b[0] - a[0])*(c[1] - a[1]) - (b[1] - a[1])*(c[0] - a[0]))/
    ((d[0] - c[0])*(b[1] - a[1]) - (b[0] - a[0])*(d[1] - c[1]));
    /* if(s >= 0 && s <= 1)
        std::cout << " r " << r << "s" << s << std::endl; */
    return (s >= 0 && s <= 1) && r >= 0;

}



bool PointInside(std::vector<float> point, std::vector<std::vector<float>> &polygon){
    int count = 0;

    for(int i = 0; i < polygon.size(); ++i){
        if(Ray_crosses(point,polygon[i],polygon[(i+1)%polygon.size()])){
            count++;
            /* std::cout << i << " " <<  (i+1)%polygon.size() << std::endl;
            std::cout << polygon[i][0] << " " <<  polygon[i][1] << std::endl;
            std::cout << polygon[(i+1)%polygon.size()][0] << " " <<  polygon[(i+1)%polygon.size()][1] << std::endl;  */
        }
    }
   // std::cout << count << std::endl;
    return count % 2 != 0;
}


glm::mat4 MatToPolygon(std::vector<float> point1,std::vector<float> point2,std::vector<float> normal){
    glm::vec3 v1 = {point2[0] - point1[0],point2[1] - point1[1],point2[2] - point1[2]};
    glm::vec3 p = {point1[0],point1[1],point1[2]};
    glm::vec3 n = {normal[0],normal[1],normal[2]};
    glm::vec3 right = glm::normalize(glm::cross(v1,n));
    glm::vec3 up = glm::normalize(glm::cross(n,right));
    return glm::lookAt(p,p + n,up);
}

Object::Object(std::vector<GLfloat> &vertexes){
    LoadObject(vertexes);
}

Object::~Object(){
    if(vertices != nullptr){
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }
}

void Smooth_shadeing(std::vector<float> &ans){
    int size = ans.size() / 6;
    std::vector<std::vector<float>> was;
    for(int i = 0; i < size; i++){
        glm::vec3 cur = glm::vec3(0.0f,0.0f,0.0f);
        for(int j = 0; j < size; j++){
            if(ans[i*6] == ans[j*6] && ans[i*6 + 1] == ans[j*6 + 1] && ans[i*6 + 2] == ans[j*6 + 2]){
                glm::vec3 norm;
                norm[0] = ans[j*6 + 3];
                norm[1] = ans[j*6 + 4];
                norm[2] = ans[j*6 + 5];
                cur = cur + norm;
            }
        }
        cur = glm::normalize(cur);
        for(int j = 0; j < size; j++){
            if(ans[i*6] == ans[j*6] && ans[i*6 + 1] == ans[j*6 + 1] && ans[i*6 + 2] == ans[j*6 + 2]){
                ans[j*6 + 3] = cur[0];
                ans[j*6 + 4] = cur[1];
                ans[j*6 + 5] = cur[2];
            }
        }
    }
}

void Object::LoadObject(std::vector<GLfloat> &vertexes){
    //Smooth_shadeing(vertexes);
    //Copy data
    
    uint64_t size = vertexes.size();
    if(size % 6 != 0){
        std::cout << "ERROR: Model have don't close polygon" << std::endl;
        return;
    }
    memcpy(vertices,vertexes.data(),sizeof(float)*vertexes.size());


    

    num_vertex = size / 6;
    std::cout<< "Data" << std::endl;
    /* for(int i = 0; i < num_vertex; ++i){
        for(int j = 0; j < 6; ++j){
            std::cout << vertices[i*6 + j] << " ";
        }
        std::cout << std::endl;
    } */
    
    //Set buffers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO); 
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*size, vertices, GL_STATIC_DRAW); 

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0); 
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Object::ConnectVAO(){
    glBindVertexArray(VAO);
}

void Object::DisconnectVAO(){
    glBindVertexArray(0);
}

uint64_t Object::GetNumVertex(){return num_vertex;}

glm::mat4 Object::GetModelMatrix(){return model;}

void Object::LoadObject(std::vector<std::vector<float>> points,std::vector<std::vector<int>> faces){
    std::vector<std::vector<std::vector<float>>> polygons;
    std::vector<std::vector<float>> normals;
    for(int i = 0; i < faces.size(); ++i){
        std::vector<std::vector<float>> polygon(faces[i].size(),std::vector<float>(3) );
        for(int j= 0; j < faces[i].size();++j){
            polygon[j][0] = points[faces[i][j]][0];
            polygon[j][1] = points[faces[i][j]][1];
            polygon[j][2] = points[faces[i][j]][2];
        }  
        polygons.push_back(polygon);
    }
    
    for(int i = 0; i < polygons.size(); ++i){
        glm::vec3 v1 = {polygons[i][1][0] - polygons[i][0][0],polygons[i][1][1] - polygons[i][0][1],polygons[i][1][2] - polygons[i][0][2]};
        glm::vec3 v2 = {polygons[i][2][0] - polygons[i][1][0],polygons[i][2][1] - polygons[i][1][1],polygons[i][2][2] - polygons[i][1][2]};
        v1 = glm::normalize(v1);
        v2 = glm::normalize(v2);
        glm::vec3 vnorm = glm::normalize(-glm::cross(v1,v2));
        std::vector<float> normal(3);
        normal[0] = vnorm[0];
        normal[1] = vnorm[1];
        normal[2] = vnorm[2];
        normals.push_back(normal);
    }

    std::vector<float> ans;
    for(int i = 0; i < polygons.size(); ++i){
        std::vector<std::vector<float>> triangul; 
        Triangulation(polygons[i],normals[i],triangul);
        for(int j = 0; j < triangul.size(); ++j){
            ans.push_back(triangul[j][0]);
            ans.push_back(triangul[j][1]);
            ans.push_back(triangul[j][2]);
            ans.push_back(normals[i][0]);
            ans.push_back(normals[i][1]);
            ans.push_back(normals[i][2]);
        }
    }
    //Smooth_shadeing(ans);
    LoadObject(ans);
}

void Object::Triangulation(std::vector<std::vector<float>> polygon,std::vector<float> normal, std::vector<std::vector<float>> &ans){
    glm::mat4 toPolyg = MatToPolygon(polygon[0],polygon[1],normal);  
    std::vector<std::vector<float>> copy_polygon (polygon.size(),std::vector<float> (3));
    for(int i =0; i < polygon.size();++i){
        glm::vec4 point = {polygon[i][0],polygon[i][1],polygon[i][2], 1.0};
        point = toPolyg * point;
        copy_polygon[i][0] = point[0];
        copy_polygon[i][1] = point[1];
        copy_polygon[i][2] = point[2];
    }
    while(polygon.size() > 3){
        for(int i = 0; i < copy_polygon.size(); ++i){
            std::vector<float> p(2);
            p[0] = (copy_polygon[(i + 2) % copy_polygon.size()][0] - copy_polygon[i][0])/2 + copy_polygon[i][0];
            p[1] = (copy_polygon[(i + 2) % copy_polygon.size()][1] - copy_polygon[i][1])/2 + copy_polygon[i][1];
            if(true){
                ans.push_back(polygon[i]);
                ans.push_back(polygon[(i + 1) % polygon.size()]);
                ans.push_back(polygon[(i + 2) % polygon.size()]);
                copy_polygon.erase(copy_polygon.begin() + (i + 1) % copy_polygon.size());
                polygon.erase(polygon.begin() + (i + 1) % polygon.size());
                break;
            }
        }
    }

    ans.push_back(polygon[0]);
    ans.push_back(polygon[1]);
    ans.push_back(polygon[2]);
}

void Object::SetModel(glm::mat4 nm){
    model = nm;
}