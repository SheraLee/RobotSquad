//
//  Geometry.cpp
//  HW3
//
//  Created by Meeta Marathe on 2/27/18.
//  Copyright © 2018 Meeta Marathe. All rights reserved.
//

#include "Geometry.h"
#include "Window.h"

Geometry::Geometry(const char* filepath, GLuint shaderProgram, glm::vec3 offset)
{
    shader = shaderProgram;
    this->offset = offset;
    parse(filepath);
    
    toWorld = glm::mat4(1.0f);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &VBO_Normal);
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &EBO_Normal);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    std::vector<int> fVerts;
    for (int i = 0; i < fvIndices.size(); i++)
    {
        fVerts.push_back(fvIndices[i].x);
        fVerts.push_back(fvIndices[i].y);
        fVerts.push_back(fvIndices[i].z);
    }
    
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Normal);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), normals.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, fVerts.size() * sizeof(int), fVerts.data(), GL_STATIC_DRAW);
    
    // Unbind buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Geometry::parse(const char* filepath)
{
    FILE *fp; //File pointer
    float x, y, z; //Certex coordinates
    float r, g, b; //Vertex color
    int c1, c2; //Characters read from file
    
    fp = fopen(filepath, "r");
    if (!fp)
    {
        std::cerr << "Error loading file." << std::endl;
        exit(-1);
    }
    
    while (true)
    {
        c1 = fgetc(fp);
        if (c1 == EOF)
        {
            break;
        }
        c2 = fgetc(fp);
        
        if (c1 == 'v' && c2 == ' ') //Vertex
        {
            fscanf(fp, "%f %f %f %f %f %f\r\n", &x, &y, &z, &r, &g, &b);
            glm::vec3 v(x, y, z);
            vertices.push_back(v);
        }
        
        else if (c1 == 'v' && c2 == 'n') //Vertex normal
        {
            fscanf(fp, "%f %f %f\r\n", &x, &y, &z);
            glm::vec3 n(x, y, z);
            normals.push_back(n);
        }
        
        else if (c1 == 'f' && c2 == ' ') //Face vertices
        {
            fscanf(fp, "%f//", &x);
            fscanf(fp, "%f ", &r);
            fscanf(fp, "%f//", &y);
            fscanf(fp, "%f ", &g);
            fscanf(fp, "%f//", &z);
            fscanf(fp, "%f \r\n", &b);
            glm::vec3 v(x - 1, y - 1, z - 1);
            glm::vec3 n(r - 1, g - 1, b - 1);
            fvIndices.push_back(v);
            fnIndices.push_back(n);
        }
        
        else
        {
            fscanf(fp, "\r\n");
        }
    }
    
    fclose(fp);
}

void Geometry::draw(glm::mat4 C)
{
    if (!posSet)
    {
        position = getPosFromCenter();
        position += offset;
        posSet = true;
    }
    toWorld = C * toWorld;
    //std::cout << position.x << " " << position.y << " "<< position.z << std::endl;
    
    glm::mat4 modelview = Window::V * toWorld;
    uProjection = glGetUniformLocation(shader, "projection");
    uModel = glGetUniformLocation(shader, "model");
    uView = glGetUniformLocation(shader, "view");
    uColor = glGetUniformLocation(shader, "color");
    uOffset = glGetUniformLocation(shader, "offset");
    
    // Now send these values to the shader program
    glUniformMatrix4fv(uProjection, 1, GL_FALSE, &Window::P[0][0]);
    glUniformMatrix4fv(uModel, 1, GL_FALSE, &toWorld[0][0]);
    glUniformMatrix4fv(uView, 1, GL_FALSE, &Window::V[0][0]);
    glUniform3f(uOffset, offset.x, offset.y, offset.z);
    glUniform1i(glGetUniformLocation(shader, "curve"), false);
    
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, sizeof(glm::vec3) * vertices.size(), GL_UNSIGNED_INT, 0);
  
    //Unbind
    glBindVertexArray(0);
}

glm::vec3 Geometry::getPosFromCenter()
{
    /*glm::vec3 max(vertices[0].x + position.x, vertices[0].y + position.y, vertices[0].z + position.z);
    glm::vec3 min(vertices[0].x + position.x, vertices[0].y + position.y, vertices[0].z + position.z);
    
    for (int i = 1; i < vertices.size(); i++)
    {
        if (vertices[i].x + position.x > max.x)
        {
            max.x = vertices[i].x + position.x;
        }
        if (vertices[i].x + position.x < min.x)
        {
            min.x = vertices[i].x + position.x;
        }
        
        if (vertices[i].y + position.y > max.y)
        {
            max.y = vertices[i].y + position.y;
        }
        if (vertices[i].y + position.y < min.y)
        {
            min.y = vertices[i].y + position.y;
        }
        
        if (vertices[i].z + position.z > max.z)
        {
            max.z = vertices[i].z + position.z;
        }
        if (vertices[i].z + position.z < min.z)
        {
            min.z = vertices[i].z + position.z;
        }
    }*/
    
    glm::vec3 max(vertices[0].x, vertices[0].y, vertices[0].z);
    glm::vec3 min(vertices[0].x, vertices[0].y, vertices[0].z);
    
    for (int i = 1; i < vertices.size(); i++)
    {
        if (vertices[i].x> max.x)
        {
            max.x = vertices[i].x;
        }
        if (vertices[i].x < min.x)
        {
            min.x = vertices[i].x;
        }
        
        if (vertices[i].y > max.y)
        {
            max.y = vertices[i].y;
        }
        if (vertices[i].y < min.y)
        {
            min.y = vertices[i].y;
        }
        
        if (vertices[i].z > max.z)
        {
            max.z = vertices[i].z;
        }
        if (vertices[i].z < min.z)
        {
            min.z = vertices[i].z;
        }
    }
    glm::vec3 center = (max + min) / 2.0f + position;
    return center;
}

