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
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
glm::mat4 interpulate(float Qua1[4], float Qua2[4], float time);
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


int main()
{

    string off = "body.off";
    Model model = LoadModel(off);
    float Qua1[4] = {0.3826834, 0, 0, 0.9238795};
    float Qua2[4] = {-0.3826834, 0, 0, 0.9238795};

    







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
    glBufferData(GL_ARRAY_BUFFER, model.numberVertex * 3 * 4, model.vertex, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.numberIndice * 3 * 4, model.indice, GL_STATIC_DRAW);
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
    glBufferData(GL_ARRAY_BUFFER, model.numberVertex * 3 * 4, model.vertex, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.numberIndice * 3 * 4, model.indice, GL_STATIC_DRAW);
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
    glBufferData(GL_ARRAY_BUFFER, model.numberVertex * 3 * 4, model.vertex, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO3);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.numberIndice * 3 * 4, model.indice, GL_STATIC_DRAW);
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
    projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH/(float)SCR_HEIGHT, -25.0f, 100.0f);

    float currentPlace = -5.0f;
    float legTime = 0;
    
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
        float time1 = glfwGetTime();
        float t = fmod(time1, 1);

        glm::mat4 body = glm::mat4(1.0f);
        currentPlace = currentPlace + 0.01f;
        body = glm::translate(body,glm::vec3(0.0f, 0.0f, currentPlace ));
        glBindVertexArray(VAO);
        glad_glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(body));
        glDrawElements(GL_TRIANGLES, model.numberIndice * 3, GL_UNSIGNED_INT, 0);
        
        legTime = legTime + 0.01f;
        glm::mat4 legLeft = glm::mat4(1.0f);
        float legTime2 = 0;
        float legTime3 = 0;
        if(legTime > 2){legTime = 0;}
        if(legTime < 1){
        glm::mat4 legLeftRotation = interpulate(Qua1, Qua2, legTime);
        legLeft = glm::translate(legLeft, glm::vec3(-0.1f, -0.5f, -0.05f));
//        legLeft = glm::translate(legLeft, glm::vec3(-0.1f, -0.5f, 0.0f));
        legLeft = legLeftRotation * legLeft;
        legLeft = glm::translate(legLeft, glm::vec3(0.0f, 0.0f, 0.05f));
        legLeft = body * legLeft;
        }
        if(legTime > 1 && legTime < 2){
            legTime2 = legTime -1;
            glm::mat4 legLeftRotation = interpulate(Qua2, Qua1, legTime2);
            legLeft = glm::translate(legLeft, glm::vec3(-0.1f, -0.5f, -0.05f));
            //        legLeft = glm::translate(legLeft, glm::vec3(-0.1f, -0.5f, 0.0f));
            legLeft = legLeftRotation * legLeft;
            legLeft = glm::translate(legLeft, glm::vec3(0.0f, 0.0f, 0.05f));
            legLeft = body * legLeft;
        }
        

        
        
        glBindVertexArray(VAO2);

        glad_glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(legLeft));
        glDrawElements(GL_TRIANGLES, model.numberIndice * 3, GL_UNSIGNED_INT, 0);
        
        
        
        glm::mat4 legRight = glm::mat4(1.0f);
        if(legTime < 1){
            glm::mat4 legRightRotation = interpulate(Qua2, Qua1, legTime);
            legRight = glm::translate(legRight, glm::vec3(0.0f, -0.5f, -0.05f));
            legRight = legRightRotation * legRight;
            legRight = glm::translate(legRight, glm::vec3(0.1f, 0.0f, 0.05f));
            legRight = body * legRight;
            
        }
        if(legTime > 1 && legTime < 2){
            legTime3 = legTime -1;
            glm::mat4 legRightRotation = interpulate(Qua1, Qua2, legTime3);
            legRight = glm::translate(legRight, glm::vec3(0.0f, -0.5f, -0.05f));
            legRight = legRightRotation * legRight;
            legRight = glm::translate(legRight, glm::vec3(0.1f, 0.0f, 0.05f));
            legRight = body * legRight;
            
        }
        
        glBindVertexArray(VAO3);
        glad_glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(legRight));
        glDrawElements(GL_TRIANGLES, model.numberIndice * 3, GL_UNSIGNED_INT, 0);
        
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

glm::mat4 interpulate(float Qua1[4], float Qua2[4], float time)
{
    float quaX[2] = {Qua1[0], Qua2[0]};
    float quaY[2] = {Qua1[1], Qua2[1]};
    float quaZ[2] = {Qua1[2], Qua2[2]};
    float quaW[2] = {Qua1[3], Qua2[3]};
    glm::vec2 Qx = glm::make_vec2(quaX);
    glm::vec2 Qy = glm::make_vec2(quaY);
    glm::vec2 Qz = glm::make_vec2(quaZ);
    glm::vec2 Qw = glm::make_vec2(quaW);
    float blendingM[4] =
    {
        -1, 1,
        1,  0
    };
    glm::mat2 M = glm::make_mat2(blendingM);
    float t[2] = {time, 1};
    glm::vec2 T = glm::make_vec2(t);
    
    glm::vec2 xT = T * M * Qx;
    float Xt = xT[0] + xT[1];
    
    glm::vec2 yT = T * M * Qy;
    float Yt = yT[0] + yT[1];
    
    glm::vec2 zT = T * M * Qz;
    float Zt = zT[0] + zT[1];
    
    glm::vec2 wT = T * M * Qw;
    float Wt = wT[0] + wT[1];
    
    float normalBase = sqrt(Xt * Xt + Yt * Yt + Zt * Zt + Wt * Wt);
    
    float normalXt = Xt / normalBase;
    float normalYt = Yt / normalBase;
    float normalZt = Zt / normalBase;
    float normalWt = Wt / normalBase;
    
    float QuaRotate[9] =
    {
        1 - 2 * normalYt * normalYt - 2 * normalZt * normalZt,
        2 * normalXt * normalYt + 2 * normalZt * normalWt,
        2 * normalXt * normalZt - 2 * normalYt * normalWt,
        2 * normalXt * normalYt - 2 * normalZt * normalWt,
        1 - 2 * normalXt * normalXt,
        2 * normalYt * normalZt + 2 * normalXt * normalWt,
        2 * normalXt * normalZt + 2 * normalYt * normalWt,
        2 * normalYt * normalZt - 2 * normalXt * normalWt,
        1 - 2 * normalXt * normalXt - 2 * normalYt * normalYt
    };
    
    glm::mat3 rotate = glm::make_mat3(QuaRotate);
    glm::mat4 transform(rotate);
    transform[3][3] = 1.0f;

    
    return transform;
}
