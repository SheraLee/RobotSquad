//
//  Curve.cpp
//  HW3
//
//  Created by Meeta Marathe on 3/1/18.
//  Copyright © 2018 Meeta Marathe. All rights reserved.
//

#include "Curve.h"
#include "Window.h"

Curve::Curve()
{
    glm::vec3 p0 (600.0f, -300.0f, 1000.0f);
    glm::vec3 p1 (400.0f, -250.0f, 1000.0f);
    glm::vec3 p2 (200.0f, -300.0f, 1000.0f);
    glm::vec3 p3 (50.0f, -210.0f, 1000.0f);
    generatePoints(p0, p1, p2, p3);
    
    p0 = p3;
    p1 = p0 + p3 - p2;
    p2 = glm::vec3(-40.0f, -400.0f, 700.0f);
    p3 = glm::vec3(-100.0f, -400.0f, 500.0f);
    generatePoints(p0, p1, p2, p3);
    
    p0 = p3;
    p1 = p0 + p3 - p2;
    p2 = glm::vec3(-200.0f, -600.0f, 500.0f);
    p3 = glm::vec3(-300.0f, -700.0f, 700.0f);
    generatePoints(p0, p1, p2, p3);
    
    p0 = p3;
    p1 = p0 + p3 - p2;
    p2 = glm::vec3(50.0f, -400.0f, 800.0f);
    p3 = glm::vec3(200.0f, -390.0f, 900.0f);
    generatePoints(p0, p1, p2, p3);
    
    p0 = p3;
    p1 = p0 + p3 - p2;
    p2 = glm::vec3(300.0f, -360.0f, 1000.0f);
    p3 = glm::vec3(600.0f, -300.0f, 1000.0f);
    generatePoints(p0, p1, p2, p3);
    
    //Set up VAO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(glm::vec3), &points[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    
    /*glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(glm::vec3), &points[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);*/
    
    // Unbind buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Curve::generatePoints(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
{
    glm::vec3 a = (-1.0f * p0) + (3.0f * p1) - (3.0f * p2) + p3;
    glm::vec3 b = (3.0f * p0) - (6.0f * p1) + (3.0f * p2);
    glm::vec3 c = (-3.0f * p0) + (3.0f * p1);
    glm::vec3 d = p0;
    glm::mat4 mat (a.x, a.y, a.z, 1.0f,
                   b.x, b.y, b.z, 1.0f,
                   c.x, c.y, c.z, 1.0f,
                   d.x, d.y, d.z, 1.0f);
    
    //Generate points
    for (int i = 0; i <= 150; i++)
    {
        glm::vec4 t (pow(i / 150.0f, 3), pow(i / 150.0f, 2), i / 150.0f,  1.0f);
        glm::vec4 point = mat * t;
        points.push_back(glm::vec3(point.x, point.y, point.z));
        std::cout << point.x << " " << point.y << " " << point.z << std::endl;
    }
}

void Curve::draw(GLuint shader)
{
    glm::mat4 toWorld (1.0f);
    glm::mat4 modelview = Window::V * toWorld;
    uProjection = glGetUniformLocation(shader, "projection");
    uModel = glGetUniformLocation(shader, "model");
    uView = glGetUniformLocation(shader, "view");
    uOffset = glGetUniformLocation(shader, "offset");
    
    // Now send these values to the shader program
    glUniformMatrix4fv(uProjection, 1, GL_FALSE, &Window::P[0][0]);
    glUniformMatrix4fv(uModel, 1, GL_FALSE, &toWorld[0][0]);
    glUniformMatrix4fv(uView, 1, GL_FALSE, &Window::V[0][0]);
    glUniform3f(uOffset, 0.0f, 0.0f, 0.0f);
    glUniform1i(glGetUniformLocation(shader, "curve"), true);
    
    //Draw curve
    //glDepthMask(GL_FALSE);
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINE_STRIP, 0, points.size());
    //glDepthMask(GL_TRUE);
    
    //Unbind
    glBindVertexArray(0);
}
