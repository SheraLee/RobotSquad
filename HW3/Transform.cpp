//
//  Transform.cpp
//  HW3
//
//  Created by Meeta Marathe on 2/27/18.
//  Copyright © 2018 Meeta Marathe. All rights reserved.
//

#include "Transform.h"

Transform::Transform()
{
    M = glm::mat4(1.0f);
}

void Transform::draw(glm::mat4 C)
{
    for (Node* child : childList)
    {
        child->draw(M * C);
    }
}

void Transform::update()
{
    for (Node* child : childList)
    {
        child->update();
    }
}

void Transform::addChild(Node* child)
{
    childList.push_back(child);
}

void Transform::removeChild()
{
    
}
