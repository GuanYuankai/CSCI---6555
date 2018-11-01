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
    ifstream myfile("body.off");
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
    
    glm::mat4 body = glm::mat4(1.0f);
    







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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    unsigned int VBO2, VAO2, EBO2;
    glGenVertexArrays(2, &VAO2);
    glGenBuffers(2, &VBO2);
    glGenBuffers(2, &EBO2);
    
    glBindVertexArray(VAO2);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, numberVertex * 3 * 4, vertex, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numberIndice * 3 * 4, indice, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    unsigned int VBO3, VAO3, EBO3;
    glGenVertexArrays(3, &VAO3);
    glGenBuffers(3, &VBO3);
    glGenBuffers(3, &EBO3);
    
    glBindVertexArray(VAO3);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO3);
    glBufferData(GL_ARRAY_BUFFER, numberVertex * 3 * 4, vertex, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO3);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numberIndice * 3 * 4, indice, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE)
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::lookAt(glm::vec3(3.0f, 3.0f, 3.0f),
                       glm::vec3(0.0f, 0.0f, 0.0f),
                       glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);

    
    while (!glfwWindowShouldClose(window))
    {
        


        processInput(window);
        
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ourShader.use();
        float time1 = glfwGetTime();
        float t = fmod(time1, 3);
        glm::mat4 body = glm::mat4(1.0f);
        body = glm::translate(body,glm::vec3(0.0f, 0.0f, 0.0f + t ));
        
        glm::mat4 legLeft = glm::mat4(1.0f);
        legLeft = glm::translate(legLeft, glm::vec3(-0.1f, -0.5f, 0.0f));
        legLeft = body * legLeft;
        
        glm::mat4 legRight = glm::mat4(1.0f);
        legRight = glm::translate(legRight, glm::vec3(0.1f, -0.5f, 0.0f));
        legRight = body * legRight;

        int viewLoc = glad_glGetUniformLocation(ourShader.ID, "view");
        glad_glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        int projLoc = glad_glGetUniformLocation(ourShader.ID, "projection");
        glad_glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
        int transLoc = glad_glGetUniformLocation(ourShader.ID, "trans");
 

 
        glBindVertexArray(VAO);
        glad_glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(body));
        glDrawElements(GL_TRIANGLES, numberIndice * 3, GL_UNSIGNED_INT, 0);
        
        glBindVertexArray(VAO2);

        glad_glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(legLeft));
        glDrawElements(GL_TRIANGLES, numberIndice * 3, GL_UNSIGNED_INT, 0);
        
        glBindVertexArray(VAO3);
        glad_glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(legRight));
        glDrawElements(GL_TRIANGLES, numberIndice * 3, GL_UNSIGNED_INT, 0);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(2, &VAO2);
    glDeleteBuffers(2, &VBO2);
    glDeleteBuffers(2, &EBO2);
    glDeleteVertexArrays(3, &VAO3);
    glDeleteBuffers(3, &VBO3);
    glDeleteBuffers(3, &EBO3);
    
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
