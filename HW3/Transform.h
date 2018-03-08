//
//  Transform.h
//  HW3
//
//  Created by Meeta Marathe on 2/27/18.
//  Copyright © 2018 Meeta Marathe. All rights reserved.
//

#ifndef Transform_h
#define Transform_h

#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdio.h>
#include <list>
#include "Node.h"

class Transform : public Node
{
private:
    glm::mat4 M;
    std::list<Node*> childList;
    
public:
    Transform();
    void draw(glm::mat4 C);
    void addChild(Node* child);
    void update();
    void removeChild();
    void updatePos(glm::vec3 pos);
};

#endif /* Transform_h */
