//
//  BindBuffer.cpp
//  Lab3
//
//  Created by Yuankai Guan on 2018/12/17.
//  Copyright © 2018年 Yuankai Guan. All rights reserved.
//
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "BindBuffer.hpp"
#include "LoadModel.h"
BufferObj BindBuffer(Model model)
{
    BufferObj bufferObj;
    glGenVertexArrays(1, &bufferObj.VAO);
    glGenBuffers(1, &bufferObj.VBO);
    glGenBuffers(1, &bufferObj.EBO);
    
    glBindVertexArray(bufferObj.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, bufferObj.VBO);
    glBufferData(GL_ARRAY_BUFFER, model.numberVertex * 3 * 4, model.vertex, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferObj.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.numberIndice * 3 * 4, model.indice, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    return bufferObj;
}
