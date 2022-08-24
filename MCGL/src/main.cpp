// #include "vendor/imgui/imgui.h"
// #include "vendor/imgui/imgui_impl_opengl3.h"
// #include "vendor/imgui/imgui_impl_glfw.h"
#include "Texture.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Cube.h"

#include <iostream>
#include <vector>
#include <unordered_map>

#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include "vendor/glm/gtc/type_ptr.hpp"


const int WIDTH = 1280;
const int HEIGHT = 720; 

void processInput(GLFWwindow* window);



int main()
{
    //#------------------Initials-------------------#// 
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL", nullptr, nullptr);

    if(!window)
    {
        std::cout << "Failed to create window\n";
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to init GLAD\n";
        exit(-1); 
    }

    glViewport(0, 0, WIDTH, HEIGHT);

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int WIDHT, int HEIGHT) {
        glViewport(0, 0, WIDTH, HEIGHT);
    });

    //#------------------Shaders and Coordinates/shapes-------------------#// 
    unsigned int ID = Shader("C:\\Dev\\OpenGL\\VSC\\OpenGL1\\src\\shader.glsl").ID;

    Cube cube;

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3
    };

    //#------------------Data buffers-------------------#// 
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    // VertexBuffer VBO(vertices, sizeof(vertices));
    VertexBuffer VBO(cube.getVertices(), cube.getSizeOfData());
    IndexBuffer IBO(indices, sizeof(indices));

    glBindVertexArray(VAO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    // glEnableVertexAttribArray(2);


    //#------------------Textures-------------------#// 
    std::unordered_map<std::string, Texture> texs;
    texs["Container"]
        .addTexture("C:\\Dev\\OpenGL\\VSC\\OpenGL1\\res\\textures\\Container.jpg");
    texs["Container"]
        .addTexture("C:\\Dev\\OpenGL\\VSC\\OpenGL1\\res\\textures\\Luigi.png");
    
    glUseProgram(ID);
    glUniform1i(glGetUniformLocation(ID, "texture1"), 0);
    glUniform1i(glGetUniformLocation(ID, "texture2"), 1);
    //#------------------Camera-------------------#//
        //where the camera is initially placed
    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
        //where the camera points to
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);

    //if we substract them we get the camera's-target direction
    //If we switch the subtraction order around we now get a vector pointing towards the camera's positive z-axis:
    glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
    
    //#------------------Transformations-------------------#//
    glm::mat4 model, view, projection = glm::mat4(1.0f);

    projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
    glUniformMatrix4fv(glGetUniformLocation(ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    float velocity = 0.0350f;
    float ForwardBack = 0.f;
    float RightLeft = 0.f;
    float TopDown = 0.f;
    
    glm::vec3 movement;
    //#------------------Additional Configuration-------------------#// 

    glEnable(GL_DEPTH_TEST);  
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //#------------------Main Rendering Loop-------------------#// 
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        //opposite of logic because we are moving the blocks, not the actual character
        if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            ForwardBack += -velocity;
        
        if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            ForwardBack += velocity;

        if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            RightLeft += -velocity; 

        if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            RightLeft += velocity;

        if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            TopDown += velocity;

        if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            TopDown += -velocity;

        movement.x = RightLeft;
        movement.y = ForwardBack;
        movement.z = TopDown;

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        texs["Container"].Bind();
        glUseProgram(ID);
        
        for(int z = 0; z < 5; z++)
        {
            for(int i = 0; i < 5; i++)
            {
                //initialize
                model = glm::mat4(1.0f);
                view = glm::mat4(1.0f);
                
                //configure positions
                model = glm::rotate(model, glm::radians(-73.0f), glm::vec3(0.5f, 0.0f, 0.0f));
                                                                    // (-z) generate blocks on next line
                model = glm::translate(model, glm::vec3(0.0f, 0.0f - z, 0.0f));

                view = glm::translate(view, glm::vec3((float)i - 2.0f , 0.0f, -10.0f));
                //send data
                glUniformMatrix4fv(
                    glGetUniformLocation(ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
                glUniformMatrix4fv(
                    glGetUniformLocation(ID, "view"), 1, GL_FALSE, glm::value_ptr(view));

                //draw
                glBindVertexArray(VAO);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
        }
        
        glfwSwapBuffers(window);
		glfwPollEvents();
    }

    //#------------------Freeing memory-------------------#// 
    glDeleteVertexArrays(1, &VAO);

    glfwTerminate();
}


void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}