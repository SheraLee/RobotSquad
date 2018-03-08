//
//  Skybox.h
//  HW3
//
//  Created by Meeta Marathe on 2/25/18.
//  Copyright © 2018 Meeta Marathe. All rights reserved.
//

#ifndef Skybox_h
#define Skybox_h

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#else
#include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

class Skybox
{
private:
    unsigned int cubemapTexture;
    int windowW;
    int windowH;
    GLuint skyboxShader;
    GLuint skyboxVAO, skyboxVBO, cubeVAO, cubeVBO;
    unsigned char* loadPPM(const char* filename, int& width, int& height);
    void loadTexture();
    
public:
    Skybox(GLuint boxShader, int width, int height);
    unsigned int loadCubemap(std::vector<std::string> faces);
    void draw();
};

#endif /* Skybox_h */
