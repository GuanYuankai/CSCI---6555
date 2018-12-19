//
//  Behavior.hpp
//  Lab4
//
//  Created by Yuankai Guan on 2018/12/18.
//  Copyright © 2018年 Yuankai Guan. All rights reserved.
//

#ifndef Behavior_hpp
#define Behavior_hpp

#include <stdio.h>
#include "LoadModel.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

void Flock(Model &model1, Model &model2, float time);
void Restrict(Model restricted_area, Model model, float time);

#endif /* Behavior_hpp */
