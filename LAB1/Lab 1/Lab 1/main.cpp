#include <iostream>
#include <fstream>
#include <math.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"

using namespace std;

int main()
{
    ifstream myfile("teapot.off");
    if(!myfile)
    {
        cout << "Fail to Open File" << endl;
    }
    
    int numberVertex, numberIndice, zero, flag;
    int i = 0;
    double indiceData1, indiceData2, indiceData3;
    myfile >> numberVertex >> numberIndice >> zero;
    double vertex[numberVertex * 3];
    double indice[numberIndice * 4];
    for(i = 0; i < numberVertex * 3; i++)
    {
        myfile >> vertex[i];
//        cout << vertex[i] << endl;
    }
    for(i = 0; i < numberIndice * 4; i += 4)
    {
        //can use flag to decide what type the indice is
        myfile >> flag >> indiceData1 >> indiceData2 >> indiceData3;
        indice[i] = indiceData1;
        indice[i+1] = indiceData2;
        indice[i+2] = indiceData3;
//        cout << indice[i] << " " << indice[i+1] << " " << indice[i+2] << endl;
    }
    
    
    float catmullRomData[16] =
    {
        -0.5,   1.5,  -1.5,   0.5,
           1,  -2.5,     2,  -0.5,
        -0.5,     0,   0.5,     0,
           0,     1,     0,     0
        
    };
    glm::mat4 catmullRomM = glm::make_mat4(catmullRomData);
    
 
    float B_splinesData[16] =
    {
        -1.0 / 6,   3.0 / 6,   -3.0 / 6,   1.0 / 6,
         3.0 / 6,  -6.0 / 6,    3.0 / 6,       0.0,
        -3.0 / 6,       0.0,    3.0 / 6,       0.0,
         1.0 / 6,   4.0 / 6,    1.0 / 6,       0.0
    };
    glm::mat4 B_SplinesM = glm::make_mat4(B_splinesData);
    
   
    float time1 = glfwGetTime();
    float t = fmod(time1, 1);
    float tData[4] = { t*t*t, t*t, t, 1};
    glm::vec4 tM = glm::make_vec4(tData);
    
    float controlPointEulerX[16] =
    {   0,  0,  0,  0,
        0.25,   0,  0,  0,
        0.5,    0,  0,  0,
        0.75,   0,  0,  0
    };
    
    float controlPointEulerY[16] =
    {
        0,      0,  0,  0,
        0.25,   0,  0,  0,
        0.5,    0,  0,  0,
        0.75,   0,  0,  0
        
    };
    float controlPointEulerZ[16] =
    {
        0,      0,  0,  0,
        0.25,   0,  0,  0,
        0.5,    0,  0,  0,
        0.75,   0,  0,  0
        
    };
    glm::mat4 EulerX = glm::make_mat4(controlPointEulerX);
    glm::mat4 EulerY = glm::make_mat4(controlPointEulerY);
    glm::mat4 EulerZ = glm::make_mat4(controlPointEulerZ);
    
    float controlPointEulerYaw[16] =
    {
        1.5705963,  0,  0,  0,
        0,  0,  0,  0,
        1.3264163,  0,  0,  0,
        0.6154797,  0,  0,  0
        
    };
    float controlPointEulerPitch[16] =
    {
        0,  0,  0,  0,
        0.7853981,  0,  0,  0,
        0,  0,  0,  0,
        0.5235988,  0,  0,  0
        
    };
    float controlPointEulerRoll[16] =
    {
        0,  0,  0,  0,
        0,  0,  0,  0,
        -0.6134645, 0,  0,  0,
        -0.1699185, 0,  0,  0
        
    };
    glm::mat4 EulerYaw = glm::make_mat4(controlPointEulerYaw);
    glm::mat4 EulerPitch = glm::make_mat4(controlPointEulerPitch);
    glm::mat4 EulerRoll = glm::make_mat4(controlPointEulerRoll);
    
    glm::vec1 EulerCatX = tM * catmullRomM * EulerX;
    glm::vec1 EulerCatY = tM * catmullRomM * EulerY;
    glm::vec1 EulerCatZ = tM * catmullRomM * EulerZ;
    glm::vec1 EulerCatYaw = tM * catmullRomM * EulerYaw;
    glm::vec1 EulerCatPitch = tM * catmullRomM * EulerPitch;
    glm::vec1 EulerCatRoll = tM * catmullRomM * EulerRoll;

   

    
    
}

