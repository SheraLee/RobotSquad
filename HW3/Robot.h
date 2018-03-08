//
//  Robot.hpp
//  HW3
//
//  Created by Meeta Marathe on 2/28/18.
//  Copyright © 2018 Meeta Marathe. All rights reserved.
//

#ifndef Robot_h
#define Robot_h

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
#include "Transform.h"
#include "Geometry.h"

#endif /* Robot_h */

class Robot : public Transform
{
private:
    glm::mat4 M;
    std::list<Node*> childList;
    Geometry * head;
    Transform * headTransform;
    Geometry * body;
    Transform * bodyTransform;
    Geometry * arm1;
    Transform * arm1Transform;
    Geometry * arm2;
    Transform * arm2Transform;
    Geometry * leg1;
    Transform * leg1Transform;
    Geometry * leg2;
    Transform * leg2Transform;
    bool headSet = false;
    bool bodySet = false;
    bool arm1Set = false;
    bool arm2Set = false;
    bool leg1Set = false;
    bool leg2Set = false;
    float limbAngle = 0.0f;
    bool up = true;
    
public:
    Robot(GLuint shader, glm::vec3 offset);
    void draw(glm::mat4 C);
    void update();
    void addChild(Node* child);
    void removeChild();
};
