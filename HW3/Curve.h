//
//  Curve.hpp
//  HW3
//
//  Created by Meeta Marathe on 3/1/18.
//  Copyright © 2018 Meeta Marathe. All rights reserved.
//

#ifndef Curve_h
#define Curve_h

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
#include <vector>
#include <math.h>

class Curve
{
private:
    GLuint VAO, VBO;
    GLuint uProjection, uModel, uView, uOffset;
    void generatePoints(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
    
public:
    Curve();
    void draw(GLuint shader);
    std::vector<glm::vec3> points;
};

#endif /* Curve_h */
