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
#include "LoadModel.h"
#include "BindBuffer.hpp"


using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


int main()
{
    
    string off = "ball.off";
    Model ball = LoadModel(off);
    string off_plane = "plane.off";
    Model plane = LoadModel(off_plane);
    

    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LAB3", NULL, NULL);
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
    Shader ourShader_plane("shader_plane.vs", "shader_plane.fs");

    BufferObj  ball_buffer;
    ball_buffer = BindBuffer(ball);
    
    
    
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::lookAt(glm::vec3(3.0f, 3.0f, 3.0f),
                       glm::vec3(0.0f, 0.0f, 0.0f),
                       glm::vec3(0.0f, 1.0f, 0.0f));
    
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
    
    float currentPlace = -5.0f;

    
    while (!glfwWindowShouldClose(window))
    {
        
        
        
        processInput(window);
        int viewLoc = glad_glGetUniformLocation(ourShader.ID, "view");
        glad_glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        int projLoc = glad_glGetUniformLocation(ourShader.ID, "projection");
        glad_glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
        int transLoc = glad_glGetUniformLocation(ourShader.ID, "trans");
        
        
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        
        ourShader.use();

        
        glm::mat4 body = glm::mat4(1.0f);
        currentPlace = currentPlace ;
        ;
        body = glm::translate(body,glm::vec3(currentPlace, 0.0f, currentPlace ));
        glBindVertexArray(ball_buffer.VAO);
        glad_glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(body));
        glDrawElements(GL_TRIANGLES, ball.numberIndice * 3, GL_UNSIGNED_INT, 0);
        

        
        
        
        

        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &ball_buffer.VAO);
    glDeleteBuffers(1, &ball_buffer.VBO);
    glDeleteBuffers(1, &ball_buffer.EBO);

    
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


