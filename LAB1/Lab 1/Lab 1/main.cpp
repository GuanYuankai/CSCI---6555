#include <iostream>
#include <fstream>

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
        myfile >> flag >> indiceData1 >> indiceData2 >> indiceData3;
        indice[i] = indiceData1;
        indice[i+1] = indiceData2;
        indice[i+2] = indiceData3;
        cout << indice[i] << " " << indice[i+1] << " " << indice[i+2] << endl;
        
    }

 
    
  
    
    
}

