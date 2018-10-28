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
#include <glm/ext.hpp>
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
    //read model from file
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
    //load vertex parameter and indice parameter
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


    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
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
    
    glEnable(GL_DEPTH_TEST);
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
    glm::mat4 view;
    view = glm::lookAt(glm::vec3(1.0f, 1.0f, 1.0f),
                       glm::vec3(0.0f, 0.0f, 0.0f),
                       glm::vec3(0.0f, 1.0f, 0.0f));
    std::cout<<glm::to_string(view)<<std::endl;


    
    while (!glfwWindowShouldClose(window))
    {
        
        processInput(window);
        
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ourShader.use();


 
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, numberIndice * 3, GL_UNSIGNED_INT, 0);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    
    
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    
    glViewport(0, 0, width, height);
}
