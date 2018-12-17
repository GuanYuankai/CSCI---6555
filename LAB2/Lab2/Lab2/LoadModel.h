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

class Model
{
public:
    int numberVertex, numberIndice;
    float *vertex;
    int *indice;
    
};

Model LoadModel(std::string off);



#endif /* LoadModel_h */
