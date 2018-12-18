//
//  LoadModel.h
//  Lab2
//
//  Created by Yuankai Guan on 2018/12/17.
//  Copyright © 2018年 Yuankai Guan. All rights reserved.
//

#ifndef LoadModel_h
#define LoadModel_h

#include<string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>


class Model
{
public:
    int numberVertex, numberIndice;
    float *vertex;
    int *indice;
    glm::vec3 velocity;
    glm::vec3 distance;
    
};

Model LoadModel(std::string off);



#endif /* LoadModel_h */
