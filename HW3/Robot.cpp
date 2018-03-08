//
//  Robot.cpp
//  HW3
//
//  Created by Meeta Marathe on 2/28/18.
//  Copyright © 2018 Meeta Marathe. All rights reserved.
//

#include "Robot.h"

Robot::Robot(GLuint shader, glm::vec3 offset)
{
    head = new Geometry("/Users/Meeta/Desktop/CSE 167/HW3/HW3/robot-parts/head.obj", shader, offset);
    body = new Geometry("/Users/Meeta/Desktop/CSE 167/HW3/HW3/robot-parts/body.obj", shader, offset);
    arm1 = new Geometry("/Users/Meeta/Desktop/CSE 167/HW3/HW3/robot-parts/limb.obj", shader, offset);
    arm2 = new Geometry("/Users/Meeta/Desktop/CSE 167/HW3/HW3/robot-parts/limb.obj", shader, offset);
    leg1 = new Geometry("/Users/Meeta/Desktop/CSE 167/HW3/HW3/robot-parts/limb.obj", shader, offset);
    leg2 = new Geometry("/Users/Meeta/Desktop/CSE 167/HW3/HW3/robot-parts/limb.obj", shader, offset);
    
    headTransform = new Transform();
    headTransform->addChild(head);
    bodyTransform = new Transform();
    bodyTransform->addChild(body);
    arm1Transform = new Transform();
    arm1Transform->addChild(arm1);
    arm2Transform = new Transform();
    arm2Transform->addChild(arm2);
    leg1Transform = new Transform();
    leg1Transform->addChild(leg1);
    leg2Transform = new Transform();
    leg2Transform->addChild(leg2);
}

void Robot::draw(glm::mat4 C)
{
    //Head
    glm::mat4 rotX = glm::mat4(1.0f);
    glm::mat4 translateOrigin = glm::mat4(1.0f);
    glm::mat4 translateBack = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::vec3 translation = glm::vec3(0.0f, 6.0f, 5.5f);
    if (!headSet)
    {
        translate = glm::translate(glm::mat4(1.0f), translation);
        head->position += translation;
        glm::vec3 center = head->getPosFromCenter();
        translateOrigin = glm::translate(glm::mat4(1.0f), center * -1.0f);
        rotX = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        translateBack = glm::translate(glm::mat4(1.0f), center);
        headSet = true;
    }
    headTransform->draw(C * translate * translateBack * rotX * translateOrigin);
    
    //body
    rotX = glm::mat4(1.0f);
    translateOrigin = glm::mat4(1.0f);
    translateBack = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translation = glm::vec3(0.0f, 0.0f, 25.0f);
    if (!bodySet)
    {
        translate = glm::translate(glm::mat4(1.0f), translation);
        body->position += translation;
        glm::vec3 center = body->getPosFromCenter();
        translateOrigin = glm::translate(glm::mat4(1.0f), center * -1.0f);
        rotX = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        translateBack = glm::translate(glm::mat4(1.0f), center);
        bodySet = true;
    }
    bodyTransform->draw(C * translate * translateBack * rotX * translateOrigin);
    
    //Arm 1
    rotX = glm::mat4(1.0f);
    translateOrigin = glm::mat4(1.0f);
    translateBack = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translation = glm::vec3(5.0f, -5.0f, 20.0f);
    if (!arm1Set)
    {
        translate = glm::translate(glm::mat4(1.0f), translation);
        arm1->position += translation;
        glm::vec3 center = arm1->getPosFromCenter();
        translateOrigin = glm::translate(glm::mat4(1.0f), center * -1.0f);
        rotX = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        translateBack = glm::translate(glm::mat4(1.0f), center);
        arm1Set = true;
    }
    arm1Transform->draw(C * translate * translateBack * rotX * translateOrigin);
    
    //Arm 2
    rotX = glm::mat4(1.0f);
    translateOrigin = glm::mat4(1.0f);
    translateBack = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translation = glm::vec3(50.0f, -5.0f, 20.0f);
    if (!arm2Set)
    {
        translate = glm::translate(glm::mat4(1.0f), translation);
        arm2->position += translation;
        glm::vec3 center = arm2->getPosFromCenter();
        translateOrigin = glm::translate(glm::mat4(1.0f), center * -1.0f);
        rotX = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        translateBack = glm::translate(glm::mat4(1.0f), center);
        arm2Set = true;
    }
    arm2Transform->draw(C * translate * translateBack * rotX * translateOrigin);
    
    //Leg1
    rotX = glm::mat4(1.0f);
    translateOrigin = glm::mat4(1.0f);
    translateBack = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translation = glm::vec3(20.0f, -10.0f, 30.0f);
    if (!leg1Set)
    {
        translate = glm::translate(glm::mat4(1.0f), translation);
        leg1->position += translation;
        glm::vec3 center = leg1->getPosFromCenter();
        translateOrigin = glm::translate(glm::mat4(1.0f), center * -1.0f);
        rotX = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        translateBack = glm::translate(glm::mat4(1.0f), center);
        leg1Set = true;
    }
    leg1Transform->draw(C * translate * translateBack * rotX * translateOrigin);
    
    //Leg2
    rotX = glm::mat4(1.0f);
    translateOrigin = glm::mat4(1.0f);
    translateBack = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translation = glm::vec3(35.0f, -10.0f, 30.0f);
    if (!leg2Set)
    {
        translate = glm::translate(glm::mat4(1.0f), translation);
        leg2->position += translation;
        glm::vec3 center = leg2->getPosFromCenter();
        translateOrigin = glm::translate(glm::mat4(1.0f), center * -1.0f);
        rotX = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        translateBack = glm::translate(glm::mat4(1.0f), center);
        leg2Set = true;
    }
    leg2Transform->draw(C * translate * translateBack * rotX * translateOrigin);
}

void Robot::update()
{
    float deg;
    if (up)
        deg = 0.1f;
    else
        deg = -0.1f;
    limbAngle += deg; //Update angle
    if (limbAngle == 0.2f)
        up = false;
    if (limbAngle == -0.2f)
        up = true;

    //Arm1
    glm::mat4 a = glm::translate(glm::mat4(1.0f), arm1->position * -1.0f); //Translate to origin
    glm::mat4 b = glm::rotate(glm::mat4(1.0f), deg / 180.0f * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 c = glm::translate(glm::mat4(1.0f), arm1->position); //Translate back
    arm1Transform->draw(c * b * a);
    
    //Arm2
    a = glm::translate(glm::mat4(1.0f), arm2->position * -1.0f); //Translate to origin
    b = glm::rotate(glm::mat4(1.0f), -deg / 180.0f * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f));
    c = glm::translate(glm::mat4(1.0f), arm2->position); //Translate back
    arm2Transform->draw(c * b * a);
    
    //Leg1
    a = glm::translate(glm::mat4(1.0f), leg1->position * -1.0f); //Translate to origin
    b = glm::rotate(glm::mat4(1.0f), -deg / 180.0f * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f));
    c = glm::translate(glm::mat4(1.0f), leg1->position); //Translate back
    leg1Transform->draw(c * b * a);
    
    //Leg2
    a = glm::translate(glm::mat4(1.0f), leg2->position * -1.0f); //Translate to origin
    b = glm::rotate(glm::mat4(1.0f), deg / 180.0f * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f));
    c = glm::translate(glm::mat4(1.0f), leg2->position); //Translate back
    leg2Transform->draw(c * b * a);
}

