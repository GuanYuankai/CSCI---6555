//
//  PhysicalEngine.hpp
//  Lab3
//
//  Created by Yuankai Guan on 2018/12/17.
//  Copyright © 2018年 Yuankai Guan. All rights reserved.
//

#ifndef PhysicalEngine_hpp
#define PhysicalEngine_hpp

#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include "LoadModel.h"

Model Accelerate(Model model, float time);
Model Velocity(Model model, float time);


#endif /* PhysicalEngine_hpp */
