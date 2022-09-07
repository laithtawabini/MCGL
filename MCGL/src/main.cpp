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
#include "Camera.h"
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include "vendor/glm/gtc/type_ptr.hpp"

void processInput(GLFWwindow* window);

//#------------------Window settings-------------------#//
const unsigned int WIDTH  = 1280;
const unsigned int HEIGHT = 720; 

//#------------------Timings---------------------#//
float deltaTime = 0.0f;
float lastFrame = 0.0f;

//#------------------Camera---------------------#//
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;
bool firstMouse = true;


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

    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xposIn, double yposIn) {
        float xpos = static_cast<float>(xposIn);
        float ypos = static_cast<float>(yposIn);

        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

        lastX = xpos;
        lastY = ypos;

        camera.ProcessMouseMovement(xoffset, yoffset);
        });
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //this is called whenever you move the cursor

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to init GLAD\n";
        exit(-1); 
    }

    glViewport(0, 0, WIDTH, HEIGHT);

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int WIDHT, int HEIGHT) {
        glViewport(0, 0, WIDTH, HEIGHT);
    });

    //#------------------Shaders and Coordinates/shapes-------------------#// 
    unsigned int shaderID = Shader("C:\\Dev\\OpenGL\\MCGL\\MCGL\\src\\shader.glsl").ID;

    Cube cube;

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    //#------------------Cube Data buffers-------------------#// 
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
        .addTexture("C:\\Dev\\OpenGL\\MCGL\\MCGL\\res\\textures\\Container.jpg");
    texs["Container"]
        .addTexture("C:\\Dev\\OpenGL\\MCGL\\MCGL\\res\\textures\\Luigi.png");
    
    glUseProgram(shaderID);
    glUniform1i(glGetUniformLocation(shaderID, "texture1"), 0);
    glUniform1i(glGetUniformLocation(shaderID, "texture2"), 1);
    
    //#------------------Transformations-------------------#//
    glm::mat4 model,
              view,
              projection = glm::mat4(1.0f);

    uint32_t modelLoc      = glGetUniformLocation(shaderID, "model"),
             viewLoc       = glGetUniformLocation(shaderID, "view"),
             projectionLoc = glGetUniformLocation(shaderID, "projection");

    projection = glm::perspective(glm::radians(60.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
    
    //#------------------Additional Configuration-------------------#// 

    glEnable(GL_DEPTH_TEST);  
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //#------------------Main Rendering Loop-------------------#// 
    while(!glfwWindowShouldClose(window))
    {

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);
        
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderID);
        texs["Container"].Bind();

        projection = glm::perspective(camera.Zoom, (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
        view = camera.GetViewMatrix();
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        for(int z = 0; z < 5; z++)
        {
            for(int i = 0; i < 5; i++)
            {
                //initialize
                model = glm::mat4(1.0f);
                
                //configure positions
                glm::vec3 positionInWorld = glm::vec3(0.0f - i, 0.0f, 0.0f - z);
                model = glm::translate(model, positionInWorld);

                //send data
                glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
                
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
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
    
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);
    
    /*if (glfwGetKey(window, GLFW_KEY_SPACE))
        eyeLocation += up * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT))
        eyeLocation -= up * cameraSpeed;*/

}

