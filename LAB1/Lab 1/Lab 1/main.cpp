#include <iostream>
#include <fstream>
#include <math.h>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

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
    
    float cx = cos(EulerCatYaw.x);
    float sx = sin(EulerCatYaw.x);
    float cy = cos(EulerCatPitch.x);
    float sy = sin(EulerCatPitch.x);
    float cz = cos(EulerCatRoll.x);
    float sz = sin(EulerCatRoll.x);
    
    float EulerRotate[9] =
    {
        cy * cz,    cz * sx * sy - cx * sz,     sx * sz + cx * cz * sy,
        cy * cz,    cx * cz + sx * sy * sz,     cx * sy * sz - cz * sz,
        -sy,        cy * sx,                    cx * cy
    };
    glm::mat3 rotate = glm::make_mat3(EulerRotate);
    
    glm::mat4 transform(rotate);
    transform[3][3] = 1.0f;
    transform[3][0] = EulerCatX.x;
    transform[3][1] = EulerCatY.x;
    transform[3][2] = EulerCatZ.x;
   
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indice), indice, GL_STATIC_DRAW);
    cout<< sizeof(indice) << endl;
    
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
