//
//  Behavior.cpp
//  Lab4
//
//  Created by Yuankai Guan on 2018/12/18.
//  Copyright © 2018年 Yuankai Guan. All rights reserved.
//

#include "Behavior.hpp"
#include <stdio.h>
#include "LoadModel.h"
#include "PhysicalEngine.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>


void Flock(Model &model1, Model &model2, float time)
{
    float distance_Flock = glm::distance(model1.position, model2.position);
    glm::vec3 reject = glm::normalize((model2.position - model1.position)) * 100.0f / (sqrt(distance_Flock));
    if(distance_Flock <= 3)
    {

        model1 = Accelerate(model1, -reject, time);
        model2 = Accelerate(model2, reject, time);
    }
    if(distance_Flock >= 10)
    {
        model1 = Accelerate(model1, reject, time);
        model2 = Accelerate(model2, -reject, time);
    }
}
void Restrict(Model restricted_area, Model model, float time)
{
    float distance_Restricted = glm::distance(restricted_area.position, model.position);
    glm::vec3 runaway = glm::normalize((restricted_area.position - model.position)) * 100.0f / (sqrt(distance_Restricted));
    if(distance_Restricted <= 5)
    {
        model = Accelerate(model, runaway, time);
    }
}
