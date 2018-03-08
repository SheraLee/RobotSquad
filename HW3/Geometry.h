//
//  Geometry.h
//  HW3
//
//  Created by Meeta Marathe on 2/27/18.
//  Copyright © 2018 Meeta Marathe. All rights reserved.
//

#ifndef Geometry_h
#define Geometry_h

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#else
#include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdio.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include "Node.h"

class Geometry : public Node
{
private:
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec3> fvIndices;
    std::vector<glm::vec3> fnIndices;
    GLuint VAO, VBO, VBO_Normal, EBO, EBO_Normal;
    GLuint uProjection, uView, uModel, uColor, uOffset;
    GLuint shader;
    bool posSet = false;
    glm::vec3 offset;
    
public:
    Geometry(const char* filepath, GLuint shaderProgram, glm::vec3 offset);
    
    void draw(glm::mat4 C);
    void update() {}
    
    void parse(const char* filepath);
    glm::vec3 getPosFromCenter();
    glm::vec3 position;
    glm::mat4 toWorld;
};

#endif /* Geometry_h */
