#include <iostream>
#include <fstream>
#include <math.h>
#include <cmath>
#include <cstring>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include "shader.h"

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main(int argc, char ** argv)
{

    ifstream myfile("teapot.off");
    if(!myfile)
    {
        cout << "Fail to Open File" << endl;
    }
    
    int numberVertex, numberIndice, zero, flag;
    int i = 0;
    int j = 0;
    double indiceData1, indiceData2, indiceData3;
    myfile >> numberVertex >> numberIndice >> zero;
    float vertex[numberVertex * 3];
    int indice[numberIndice * 4];
    for(i = 0; i < numberVertex * 3; i++)
    {
        myfile >> vertex[i];
    }
    

    
    for(i = 0; i < numberIndice * 4; i += 4)
    {
        //can use flag to decide what type the indice is
        myfile >> flag >> indiceData1 >> indiceData2 >> indiceData3;
        indice[j] = indiceData1;
        j++;
        indice[j] = indiceData2;
        j++;
        indice[j] = indiceData3;
        j++;

    }

    float catmullRomData[16] =
    {

        -0.5,   1,   -0.5,  0,
        1.5,    -2.5,   0,  1,
        -1.5,   2,  0.5,    0,
        0.5,    -0.5,   0,  0
        
    };
    glm::mat4 catmullRomM = glm::make_mat4(catmullRomData);
    
 
    float B_splinesData[16] =
    {
        
        -1.0 / 6,    3.0 / 6,    -3.0 / 6,   1.0 / 6,
        3.0 / 6,    -6.0 / 6,         0.0,   4.0 / 6,
        -3.0 / 6,    3.0 / 6,    3.0 / 6,    1.0 / 6,
        1.0 / 6,         0.0,        0.0,        0.0
    };
    glm::mat4 B_SplinesM = glm::make_mat4(B_splinesData);
    
    glm::mat4 BlendingM;
    
    if(strcmp(argv[1], "C") == 0) {
        BlendingM = catmullRomM;
    }else{
        BlendingM = B_SplinesM;
    }
   
    float time1 = glfwGetTime();
//    float t = fmod(time1, 1);
    float t = 0.5;

    float tData[4] = { t*t*t, t*t, t, 1};
    glm::vec4 tM = glm::make_vec4(tData);
    
    float controlPointX[4] =
    {
        -1, -0.8, 0.8, 1
    };
    
    float controlPointY[4] =
    {
         0, 1, -1, 0
    };
    float controlPointZ[4] =
    {
        -0.5, -0.4, 0.5, 0.75
    };
    
    glm::vec4 X = glm::make_vec4(controlPointX);
    glm::vec4 Y = glm::make_vec4(controlPointY);
    glm::vec4 Z = glm::make_vec4(controlPointZ);
    
    float controlPointQuaX[4] =
    {
        0.7070341, 0, 0.05869129, 0.2705979
    };
    float controlPointQuaY[4] =
    {
        0, 0.387298, 0.1858919, 0.2705981
    };
    float controlPointQuaZ[4] =
    {
        0, 0, -0.2379391, -0.00000001
        
    };
    float controlPointQuaW[4] =
    {
        0.7071795, 0.9219546, 0.7512406, 0.785398
    };
    glm::vec4 QuaX = glm::make_vec4(controlPointQuaX);
    glm::vec4 QuaY = glm::make_vec4(controlPointQuaY);
    glm::vec4 QuaZ = glm::make_vec4(controlPointQuaZ);
    glm::vec4 QuaW = glm::make_vec4(controlPointQuaW);
    
    glm::vec4 Xt = tM * BlendingM * X;
    float Xts = Xt[0] + Xt[1] + Xt[2] + Xt[3];
    glm::vec4 Yt = tM * BlendingM * Y;
    float Yts = Yt[0] + Yt[1] + Yt[2] + Yt[3];
    glm::vec4 Zt = tM * BlendingM * Z;
    float Zts = Zt[0] + Zt[1] + Zt[2] + Zt[3];
    glm::vec4 QuaXt = tM * BlendingM * QuaX;
    float QuaXts = QuaXt[0] + QuaXt[1] + QuaXt[2] + QuaXt[3];
    glm::vec4 QuaYt = tM * BlendingM * QuaY;
    float QuaYts = QuaYt[0] + QuaYt[1] + QuaYt[2] + QuaYt[3];
    glm::vec4 QuaZt = tM * BlendingM * QuaZ;
    float QuaZts = QuaZt[0] + QuaZt[1] + QuaZt[2] + QuaZt[3];
    glm::vec4 QuaWt = tM * BlendingM * QuaW;
    float QuaWts = QuaWt[0] + QuaWt[1] + QuaWt[2] + QuaWt[3];
    
    cout << QuaXts << " " << QuaYts << " " << QuaZts << " "<< QuaWts;

    
    float normalBase = sqrt(QuaXts*QuaXts + QuaYts*QuaYts + QuaZts*QuaZts + QuaWts*QuaWts);
    cout << normalBase << endl;
    
    float nQuaX = QuaXts / normalBase;
    float nQuaY = QuaYts / normalBase;
    float nQuaZ = QuaZts / normalBase;
    float nQuaW = QuaWts / normalBase;
    cout << nQuaX << " " << nQuaY << " " << nQuaZ << " "<< nQuaW << endl;

    

    
    float QuaRotate[9] =
    {
        1 - 2 * nQuaY * nQuaY - 2 * nQuaZ * nQuaZ,
        2 * nQuaX * nQuaY + 2 * nQuaZ * nQuaW,
        2 * nQuaX * nQuaZ - 2 * nQuaY * nQuaW,
        2 * nQuaX * nQuaY - 2 * nQuaZ * nQuaW,
        1 - 2 * nQuaX * nQuaX,
        2 * nQuaY * nQuaZ + 2 * nQuaX * nQuaW,
        2 * nQuaX * nQuaZ + 2 * nQuaY * nQuaW,
        2 * nQuaY * nQuaZ - 2 * nQuaX * nQuaW,
        1 - 2 * nQuaX * nQuaX - 2 * nQuaY * nQuaY
    };
    glm::mat3 rotate = glm::make_mat3(QuaRotate);
    
    glm::mat4 transform(rotate);
    transform[3][3] = 1.0f;
    transform[3][0] = Xts;
    transform[3][1] = Yts;
    transform[3][2] = Zts;

    
   
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif
    
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LAB1", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    // glad: load all OpenGL function pointers

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    

    Shader ourShader("shader.vs", "shader.fs");
    
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, numberVertex * 3 * 4, vertex, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numberIndice * 3 * 4, indice, GL_STATIC_DRAW);
//    cout<< numberIndice * 3 * 4 << endl;
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    while (!glfwWindowShouldClose(window))
    {

        processInput(window);
        

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ourShader.use();
        
        
        float time1 = glfwGetTime();
        float t = fmod(time1, 1);
        
        float tData[4] = { t*t*t, t*t, t, 1};
        glm::vec4 tM = glm::make_vec4(tData);
        
        float controlPointX[4] =
        {
            -1, -0.8, 0.8, 1
        };
        
        float controlPointY[4] =
        {
            0, 1, -1, 0
        };
        float controlPointZ[4] =
        {
            -0.5, -0.4, 0.5, 0.75
        };
        
        glm::vec4 X = glm::make_vec4(controlPointX);
        glm::vec4 Y = glm::make_vec4(controlPointY);
        glm::vec4 Z = glm::make_vec4(controlPointZ);
        
        float controlPointQuaX[4] =
        {
            0.7070341, 0, 0.05869129, 0.2705979
        };
        float controlPointQuaY[4] =
        {
            0, 0.387298, 0.1858919, 0.2705981
        };
        float controlPointQuaZ[4] =
        {
            0, 0, -0.2379391, -0.00000001
            
        };
        float controlPointQuaW[4] =
        {
            0.7071795, 0.9219546, 0.7512406, 0.785398
        };
        glm::vec4 QuaX = glm::make_vec4(controlPointQuaX);
        glm::vec4 QuaY = glm::make_vec4(controlPointQuaY);
        glm::vec4 QuaZ = glm::make_vec4(controlPointQuaZ);
        glm::vec4 QuaW = glm::make_vec4(controlPointQuaW);
        
        glm::vec4 Xt = tM * BlendingM * X;
        float Xts = Xt[0] + Xt[1] + Xt[2] + Xt[3];
        glm::vec4 Yt = tM * BlendingM * Y;
        float Yts = Yt[0] + Yt[1] + Yt[2] + Yt[3];
        glm::vec4 Zt = tM * BlendingM * Z;
        float Zts = Zt[0] + Zt[1] + Zt[2] + Zt[3];
        glm::vec4 QuaXt = tM * BlendingM * QuaX;
        float QuaXts = QuaXt[0] + QuaXt[1] + QuaXt[2] + QuaXt[3];
        glm::vec4 QuaYt = tM * BlendingM * QuaY;
        float QuaYts = QuaYt[0] + QuaYt[1] + QuaYt[2] + QuaYt[3];
        glm::vec4 QuaZt = tM * BlendingM * QuaZ;
        float QuaZts = QuaZt[0] + QuaZt[1] + QuaZt[2] + QuaZt[3];
        glm::vec4 QuaWt = tM * BlendingM * QuaW;
        float QuaWts = QuaWt[0] + QuaWt[1] + QuaWt[2] + QuaWt[3];
        
        float normalBase = sqrt(QuaXts*QuaXts + QuaYts*QuaYts + QuaZts*QuaZts + QuaWts*QuaWts);
        float nQuaX = QuaXts / normalBase;
        float nQuaY = QuaYts / normalBase;
        float nQuaZ = QuaZts / normalBase;
        float nQuaW = QuaWts / normalBase;
        
        
        
        
        float QuaRotate[9] =
        {
            1 - 2 * nQuaY * nQuaY - 2 * nQuaZ * nQuaZ,
            2 * nQuaX * nQuaY + 2 * nQuaZ * nQuaW,
            2 * nQuaX * nQuaZ - 2 * nQuaY * nQuaW,
            2 * nQuaX * nQuaY - 2 * nQuaZ * nQuaW,
            1 - 2 * nQuaX * nQuaX,
            2 * nQuaY * nQuaZ + 2 * nQuaX * nQuaW,
            2 * nQuaX * nQuaZ + 2 * nQuaY * nQuaW,
            2 * nQuaY * nQuaZ - 2 * nQuaX * nQuaW,
            1 - 2 * nQuaX * nQuaX - 2 * nQuaY * nQuaY
        };
        glm::mat3 rotate = glm::make_mat3(QuaRotate);
        
        glm::mat4 transform(rotate);
        transform[3][3] = 1.0f;
        transform[3][0] = Xts;
        transform[3][1] = Yts;
        transform[3][2] = Zts;
//    cout << to_string(transform) << endl;
        unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, numberIndice * 3, GL_UNSIGNED_INT, 0);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
