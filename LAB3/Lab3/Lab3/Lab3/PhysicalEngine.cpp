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
    float gravity = -10.0f;
    model.velocity = glm::vec3(accelerate * time);
    model.velocity.y = model.velocity.y - gravity * time;
    return model;
}

Model Velocity(Model model, float time)
{
    model.distance = glm::vec3(model.velocity * time);
    return model;
}
