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
    
    int numberVertex, numberIndice, zero;
    int i = 0;
    double indiceData;
    myfile >> numberVertex >> numberIndice >> zero;
    double vertex[numberVertex * 3];
    double indice[numberIndice * 4];
    for(i = 0; i < numberVertex * 3; i++)
    {
        myfile >> vertex[i];
//        cout << vertex[i] << endl;
    }
    for(i = 0; i < numberIndice * 4; i++)
    {
        myfile >> indiceData;

        }

    }
    
  
    
    
}

