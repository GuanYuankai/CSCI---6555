#include <iostream>
#include <fstream>
#include <math.h>
#include <cmath>

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

int main()
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
    
    float controlPointEulerX[4] =
    {-0.5, -0.4, 0.5, 0.75};
    
    float controlPointEulerY[16] =
    {
        -0.5, -0.4, 0.5, 0.75
    };
    float controlPointEulerZ[16] =
    {
        -0.5, -0.4, 0.5, 0.75
    };
    glm::vec4 EulerX = glm::make_vec4(controlPointEulerX);
    glm::vec4 EulerY = glm::make_vec4(controlPointEulerY);
    glm::vec4 EulerZ = glm::make_vec4(controlPointEulerZ);
    
    float controlPointEulerYaw[16] =
    {
        1.5705963, 0, 1.3264163, 0.6154797
    };
    float controlPointEulerPitch[16] =
    {
        0, 0.7853981, 0, 0.5235988
    };
    float controlPointEulerRoll[16] =
    {
        0, 0, -0.6134645, -0.1699185
        
    };
    glm::vec4 EulerYaw = glm::make_vec4(controlPointEulerYaw);
    glm::vec4 EulerPitch = glm::make_vec4(controlPointEulerPitch);
    glm::vec4 EulerRoll = glm::make_vec4(controlPointEulerRoll);
    
    glm::vec4 EulerCatX = tM * catmullRomM * EulerX;
    float ECX = EulerCatX[0] + EulerCatX[1] + EulerCatX[2] + EulerCatX[3];
    glm::vec4 EulerCatY = tM * catmullRomM * EulerY;
    float ECY = EulerCatY[0] + EulerCatY[1] + EulerCatY[2] + EulerCatY[3];
    glm::vec4 EulerCatZ = tM * catmullRomM * EulerZ;
    float ECZ = EulerCatZ[0] + EulerCatZ[1] + EulerCatZ[2] + EulerCatZ[3];
    glm::vec1 EulerCatYaw = tM * catmullRomM * EulerYaw;
    float ECYaw = EulerCatYaw[0] + EulerCatYaw[1] + EulerCatYaw[2] + EulerCatYaw[3];
    glm::vec1 EulerCatPitch = tM * catmullRomM * EulerPitch;
    float ECPitch = EulerCatPitch[0] + EulerCatPitch[1] + EulerCatPitch[2] + EulerCatPitch[3];
    glm::vec1 EulerCatRoll = tM * catmullRomM * EulerRoll;
    float ECRoll = EulerCatRoll[0] + EulerCatRoll[1] + EulerCatRoll[2] + EulerCatRoll[3];
    
    float cx = cos(ECYaw);
    float sx = sin(ECYaw);
    float cy = cos(ECPitch);
    float sy = sin(ECPitch);
    float cz = cos(ECRoll);
    float sz = sin(ECRoll);
    
    float EulerRotate[9] =
    {
        cy * cz,    cz * sx * sy - cx * sz,     sx * sz + cx * cz * sy,
        cy * cz,    cx * cz + sx * sy * sz,     cx * sy * sz - cz * sz,
        -sy,        cy * sx,                    cx * cy
    };
    glm::mat3 rotate = glm::make_mat3(EulerRotate);
    
    glm::mat4 transform(rotate);
    transform[3][3] = 1.0f;
    transform[3][0] = ECX;
    transform[3][1] = ECY;
    transform[3][2] = ECZ;
    cout << to_string(transform) << endl;
    
   
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
        
        float controlPointEulerX[4] =
        {-0.5, -0.4, 0.5, 0.75};
        
        float controlPointEulerY[16] =
        {
            -0.5, -0.4, 0.5, 0.75
        };
        float controlPointEulerZ[16] =
        {
            -0.5, -0.4, 0.5, 0.75
        };
        glm::vec4 EulerX = glm::make_vec4(controlPointEulerX);
        glm::vec4 EulerY = glm::make_vec4(controlPointEulerY);
        glm::vec4 EulerZ = glm::make_vec4(controlPointEulerZ);
        
        float controlPointEulerYaw[16] =
        {
            1.5705963, 0, 1.3264163, 0.6154797
        };
        float controlPointEulerPitch[16] =
        {
            0, 0.7853981, 0, 0.5235988
        };
        float controlPointEulerRoll[16] =
        {
            0, 0, -0.6134645, -0.1699185
            
        };
        glm::vec4 EulerYaw = glm::make_vec4(controlPointEulerYaw);
        glm::vec4 EulerPitch = glm::make_vec4(controlPointEulerPitch);
        glm::vec4 EulerRoll = glm::make_vec4(controlPointEulerRoll);
        
        glm::vec4 EulerCatX = tM * catmullRomM * EulerX;
        float ECX = EulerCatX[0] + EulerCatX[1] + EulerCatX[2] + EulerCatX[3];
        glm::vec4 EulerCatY = tM * catmullRomM * EulerY;
        float ECY = EulerCatY[0] + EulerCatY[1] + EulerCatY[2] + EulerCatY[3];
        glm::vec4 EulerCatZ = tM * catmullRomM * EulerZ;
        float ECZ = EulerCatZ[0] + EulerCatZ[1] + EulerCatZ[2] + EulerCatZ[3];
        glm::vec1 EulerCatYaw = tM * catmullRomM * EulerYaw;
        float ECYaw = EulerCatYaw[0] + EulerCatYaw[1] + EulerCatYaw[2] + EulerCatYaw[3];
        glm::vec1 EulerCatPitch = tM * catmullRomM * EulerPitch;
        float ECPitch = EulerCatPitch[0] + EulerCatPitch[1] + EulerCatPitch[2] + EulerCatPitch[3];
        glm::vec1 EulerCatRoll = tM * catmullRomM * EulerRoll;
        float ECRoll = EulerCatRoll[0] + EulerCatRoll[1] + EulerCatRoll[2] + EulerCatRoll[3];
        
        float cx = cos(ECYaw);
        float sx = sin(ECYaw);
        float cy = cos(ECPitch);
        float sy = sin(ECPitch);
        float cz = cos(ECRoll);
        float sz = sin(ECRoll);
        
        float EulerRotate[9] =
        {
            cy * cz,    cz * sx * sy - cx * sz,     sx * sz + cx * cz * sy,
            cy * cz,    cx * cz + sx * sy * sz,     cx * sy * sz - cz * sz,
            -sy,        cy * sx,                    cx * cy
        };
        glm::mat3 rotate = glm::make_mat3(EulerRotate);
        
        glm::mat4 transform(rotate);
        transform[3][3] = 1.0f;
        transform[3][0] = ECX;
        transform[3][1] = ECY;
        transform[3][2] = ECZ;
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
