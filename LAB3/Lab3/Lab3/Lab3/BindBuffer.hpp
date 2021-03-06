//
//  BindBuffer.hpp
//  Lab3
//
//  Created by Yuankai Guan on 2018/12/17.
//  Copyright © 2018年 Yuankai Guan. All rights reserved.
//

#ifndef BindBuffer_hpp
#define BindBuffer_hpp

#include <stdio.h>
#include "LoadModel.h"
class BufferObj
{
public:
    unsigned int VAO, VBO, EBO;
};

BufferObj BindBuffer(Model model);
#endif /* BindBuffer_hpp */
