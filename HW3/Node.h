//
//  Node.h
//  HW3
//
//  Created by Meeta Marathe on 2/27/18.
//  Copyright © 2018 Meeta Marathe. All rights reserved.
//

#ifndef Node_h
#define Node_h

#include <stdio.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>

class Node
{
public:
    virtual void draw(glm::mat4 C) = 0;
    virtual void update() = 0;
};

#endif /* Node_h */
