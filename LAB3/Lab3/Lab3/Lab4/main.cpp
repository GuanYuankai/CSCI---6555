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
#include "PhysicalEngine.hpp"
#include "Behavior.hpp"


using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void processInput(GLFWwindow *window);
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
float lookat_Y = 50.0f;
float lookat_X = 50.0f;
float lookat_Z = 50.0f;


int main()
{
    
    string off = "ball.off";
    Model ball1 = LoadModel(off);
    Model ball2 = LoadModel(off);
    Model ball3 = LoadModel(off);
    Model ball4 = LoadModel(off);
    string off_plane = "plane.off";
    Model plane = LoadModel(off_plane);
    string off_cube = "cube.off";
    Model cube = LoadModel(off_cube);

    
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
    Shader ourShader_Plane("shader_plane.vs", "shader_plane.fs");

    BufferObj  ball1_buffer;
    ball1_buffer = BindBuffer(ball1);
    
    BufferObj ball2_buffer;
    ball2_buffer = BindBuffer(ball2);
    
    BufferObj ball3_buffer;
    ball3_buffer = BindBuffer(ball3);
    
    BufferObj ball4_buffer;
    ball4_buffer = BindBuffer(ball4);
    
    BufferObj plane_buffer;
    plane_buffer = BindBuffer(plane);
    
    BufferObj cube_buffer;
    cube_buffer = BindBuffer(cube);
    
    
    
    

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::lookAt(glm::vec3(lookat_X, lookat_Y, lookat_Z),
                       glm::vec3(0.0f, 0.0f, 0.0f),
                       glm::vec3(0.0f, 1.0f, 0.0f));
    
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 1000.0f);
    
    

    ball1.velocity = glm::vec3(5.0f, 0.0f, 3.0f);
    ball2.velocity = glm::vec3(-5.0f, 0.0f, 3.0f);
    ball3.velocity = glm::vec3(0.0f, 0.0f, 10.0f);
    ball4.velocity = glm::vec3(3.0f, 6.0f, 10.0f);
    
    cube.velocity = glm::vec3(0.0f, 0.0f, 0.0f);
    
    glm::mat4 trans = glm::mat4(1.0f);
    ball1.position = glm::vec3(-10.0f, 5.0f, 5.0f);
    ball2.position = glm::vec3(10.0f,5.0f, 5.0f);
    ball3.position = glm::vec3(3.0f,15.0f, 5.0f);
    ball4.position = glm::vec3(0.0f,2.0f, 5.0f);
    
    cube.position = glm::vec3(0.0f, 0.0f, 25.0f);
    
    glfwSetKeyCallback(window, key_callback);
    
    while (!glfwWindowShouldClose(window))
    {
        
        

        processInput(window);
        ourShader.use();
        
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::lookAt(glm::vec3(lookat_X, lookat_Y, lookat_Z),
                           glm::vec3(0.0f, 0.0f, 0.0f),
                           glm::vec3(0.0f, 1.0f, 0.0f));
        
        int viewLoc = glad_glGetUniformLocation(ourShader.ID, "view");
        glad_glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        int projLoc = glad_glGetUniformLocation(ourShader.ID, "projection");
        glad_glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
        int transLoc = glad_glGetUniformLocation(ourShader.ID, "trans");
        
        ourShader_Plane.use();
        int viewLoc_Plane = glad_glGetUniformLocation(ourShader_Plane.ID, "view");
        glad_glUniformMatrix4fv(viewLoc_Plane, 1, GL_FALSE, glm::value_ptr(view));
        int projLoc_Plane = glad_glGetUniformLocation(ourShader_Plane.ID, "projection");
        glad_glUniformMatrix4fv(projLoc_Plane, 1, GL_FALSE, glm::value_ptr(projection));
        int transLoc_Plane = glad_glGetUniformLocation(ourShader_Plane.ID, "trans");
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ourShader.use();
        
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        float time = 0.02f;
        Flock(ball1, ball2, time);
        Flock(ball2, ball3, time);
        Flock(ball1, ball3, time);
        Flock(ball1, ball4, time);
        Flock(ball2, ball4, time);
        Flock(ball3, ball4, time);
 


        
        ball1 = Velocity(ball1, time);
        trans[3] = glm::vec4(ball1.position, 1.0f);
        glBindVertexArray(ball1_buffer.VAO);
        glad_glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(trans));
        glDrawElements(GL_TRIANGLES, ball1.numberIndice * 3, GL_UNSIGNED_INT, 0);
        ball1 = Boundarybounce(ball1);
        


        ball2 = Velocity(ball2, time);
        trans[3] = glm::vec4(ball2.position, 1.0f);
        glBindVertexArray(ball2_buffer.VAO);
        glad_glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(trans));
        glDrawElements(GL_TRIANGLES, ball2.numberIndice * 3, GL_UNSIGNED_INT, 0);
        ball2 = Boundarybounce(ball2);
        
 
        ball3 = Velocity(ball3, time);
        trans[3] = glm::vec4(ball3.position, 1.0f);
        glBindVertexArray(ball3_buffer.VAO);
        glad_glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(trans));
        glDrawElements(GL_TRIANGLES, ball3.numberIndice * 3, GL_UNSIGNED_INT, 0);
        ball3 = Boundarybounce(ball3);
        
        ball4 = Velocity(ball4, time);
        trans[3] = glm::vec4(ball4.position, 1.0f);
        glBindVertexArray(ball4_buffer.VAO);
        glad_glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(trans));
        glDrawElements(GL_TRIANGLES, ball4.numberIndice * 3, GL_UNSIGNED_INT, 0);
        ball4 = Boundarybounce(ball4);

        
        Collision(ball1, ball2);
        Collision(ball1, ball3);
        Collision(ball3, ball2);
        Collision(ball1, ball4);
        Collision(ball2, ball4);
        Collision(ball3, ball4);
        

        
        ourShader_Plane.use();
        
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glm::mat4 plane_tranc = glm::mat4(1.0f);
        glBindVertexArray(plane_buffer.VAO);
        glad_glUniformMatrix4fv(transLoc_Plane, 1, GL_FALSE, glm::value_ptr(plane_tranc));
        glDrawElements(GL_TRIANGLES, plane.numberIndice * 3, GL_UNSIGNED_INT, 0);
        
//        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//        glm::mat4 cube_tranc = glm::mat4(1.0f);
//        glBindVertexArray(cube_buffer.VAO);
//        glad_glUniformMatrix4fv(transLoc_Plane, 1, GL_FALSE, glm::value_ptr(cube_tranc));
//        glDrawElements(GL_TRIANGLES, cube.numberIndice * 3, GL_UNSIGNED_INT, 0);
//

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &plane_buffer.VAO);
    glDeleteBuffers(1, &plane_buffer.VBO);
    glDeleteBuffers(1, &plane_buffer.EBO);
    
    glDeleteVertexArrays(1, &ball1_buffer.VAO);
    glDeleteBuffers(1, &ball1_buffer.VBO);
    glDeleteBuffers(1, &ball1_buffer.EBO);
    
    glDeleteVertexArrays(1, &ball2_buffer.VAO);
    glDeleteBuffers(1, &ball2_buffer.VBO);
    glDeleteBuffers(1, &ball2_buffer.EBO);
    
    glDeleteVertexArrays(1, &ball3_buffer.VAO);
    glDeleteBuffers(1, &ball3_buffer.VBO);
    glDeleteBuffers(1, &ball3_buffer.EBO);
    
    glDeleteVertexArrays(1, &ball4_buffer.VAO);
    glDeleteBuffers(1, &ball4_buffer.VBO);
    glDeleteBuffers(1, &ball4_buffer.EBO);

    
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

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_UP && action == GLFW_PRESS)
        lookat_Y += 1.0f;
    
    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
        lookat_Y -= 1.0f;
    
    if (key == GLFW_KEY_A && action == GLFW_PRESS)
        lookat_X -= 1.0f;
    
    
    if (key == GLFW_KEY_D && action == GLFW_PRESS)
        lookat_X += 1.0f;
    
    if (key == GLFW_KEY_S && action == GLFW_PRESS)
        lookat_Z += 1.0f;
    
    if (key == GLFW_KEY_W && action == GLFW_PRESS)
        lookat_Z += 1.0f;
}
