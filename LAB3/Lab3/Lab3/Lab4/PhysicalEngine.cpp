//
//  PhysicalEngine.cpp
//  Lab3
//
//  Created by Yuankai Guan on 2018/12/17.
//  Copyright © 2018年 Yuankai Guan. All rights reserved.
//

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include "PhysicalEngine.hpp"


Model Accelerate(Model model, glm::vec3 accelerate,float time)
{
//    float gravity = 1.0f;
    model.velocity = model.velocity + glm::vec3(accelerate * time);
//    model.velocity.y = model.velocity.y - gravity * time; //gravity system
    return model;
}

Model Velocity(Model model, float time)
{
    model.position =  model.position + model.velocity * time;
    return model;
}

Model Boundarybounce(Model model)
{
    if(model.position.y <= 1)
    {
        model.velocity.y = - model.velocity.y;
    }
    if(model.position.y >= 30)
    {
        model.velocity.y = - model.velocity.y;
    }
    
    
    if((model.position.x) <= -24 || (model.position.x) >= 24)
    {
        model.velocity.x = -model.velocity.x;
        
    }
    
    if((model.position.z) <= -24 || (model.position.z) >= 24)
    {
        model.velocity.z = -model.velocity.z;
        
    }
    return model;

    
}

void Collision(Model &model1, Model &model2)
{
    glm::vec3 Temporal = glm::vec3(1.0f);
    if(glm::distance(model1.position, model2.position) <= 1)
    {
        if((model1.position.x - model2.position.x <= 1) || (model2.position.x - model1.position.x <= 1))
        {
            Temporal.x = model1.position.x;
            model1.position.x = model2.position.x;
            model2.position.x = Temporal.x;
        }
        if((model1.position.z - model2.position.z <= 1) || (model2.position.z - model1.position.z <= 1))
        {
            Temporal.z = model1.position.z;
            model1.position.z = model2.position.z;
            model2.position.z = Temporal.z;
        }
    }
}
