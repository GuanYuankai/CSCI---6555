//
//  LoadModel.cpp
//  Lab2
//
//  Created by Yuankai Guan on 2018/12/17.
//  Copyright © 2018年 Yuankai Guan. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <fstream>
#include "LoadModel.h"

using namespace std;
Model LoadModel(string off)
{
    Model model;
    ifstream myfile(off);
    if(!myfile)
    {
        cout << "Fail to Open File" << endl;
    }
    
    int zero, flag;
    int i = 0;
    int j = 0;
    double indiceData1, indiceData2, indiceData3;
    myfile >> model.numberVertex >> model.numberIndice >> zero;
    model.vertex = new float[model.numberVertex * 3];
    model.indice = new int[model.numberIndice * 4];
    //load vertex parameter and indice parameter
    for(i = 0; i < model.numberVertex * 3; i++)
    {
        myfile >> model.vertex[i];
    }
    
    
    
    for(i = 0; i < model.numberIndice * 4; i += 4)
    {
        //can use flag to decide what type the indice is
        myfile >> flag >> indiceData1 >> indiceData2 >> indiceData3;
        model.indice[j] = indiceData1;
        j++;
        model.indice[j] = indiceData2;
        j++;
        model.indice[j] = indiceData3;
        j++;
        
    }
    return model;
}
