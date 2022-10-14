// #include "vendor/imgui/imgui.h"
// #include "vendor/imgui/imgui_impl_opengl3.h"
// #include "vendor/imgui/imgui_impl_glfw.h"
#include "Texture.h"

#include "graphics/Shader.h"
#include "graphics/VertexArray.h"

#include "world/Cube.h"
#include "camera/Camera.h"

#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include "vendor/glm/gtc/type_ptr.hpp"


void processInput(GLFWwindow* window);
void mouse_movement_callback(GLFWwindow* window, double xposIn, double yposIn);


//#------------------Window settings-------------------#//
const unsigned int WIDTH = 1280;
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

    if (!window)
    {
        std::cout << "Failed to create window\n";
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(window);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_movement_callback);
    //this is called whenever you move the cursor

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to init GLAD\n";
        exit(-1);
    }

    glViewport(0, 0, WIDTH, HEIGHT);

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int WIDHT, int HEIGHT) {
        glViewport(0, 0, WIDTH, HEIGHT);
        });

    //#------------------Shaders and Coordinates/shapes to be rendered-------------------#// 
    Shader cubeShader("C:\\Dev\\OpenGL\\MCGL\\MCGL\\res\\shaders\\shader.glsl");
    Cube cube;

    //#------------------Cube Data buffers-------------------#// 
    VertexArray VAO;
    VertexBuffer VBO(&(cube.getVertices()[0]), cube.getSizeOfData());
    VertexBufferLayout layout;

    layout.PushElement(GL_FLOAT, 3);
    layout.PushElement(GL_FLOAT, 2);

    VAO.AddBuffer(VBO, layout);

    //#------------------Textures-------------------#// 
    std::unordered_map<std::string, Texture> texs;
    std::set<int> set;

    texs["Container"]
        .addTexture("C:\\Dev\\OpenGL\\MCGL\\MCGL\\res\\textures\\Container.jpg");
    texs["Container"]
        .addTexture("C:\\Dev\\OpenGL\\MCGL\\MCGL\\res\\textures\\Luigi.png");

    cubeShader.Use();
    cubeShader.SetUniform1i("texture1", 0);
    cubeShader.SetUniform1i("texture2", 1);

    //#------------------Transformations-------------------#//
    glm::mat4 modelMat,
              viewMat,
              projectionMat = glm::mat4(1.0f);


    projectionMat = glm::perspective(glm::radians(60.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
    cubeShader.SetUniformMat4("projection", projectionMat);
    //#------------------Additional Configuration-------------------#// 
    
    glEnable(GL_DEPTH_TEST);
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    

    //#------------------Main Rendering Loop-------------------#// 
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);
  
        glm::vec3 clearColor = glm::normalize(glm::vec3(0, 230, 240));
        glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cubeShader.Use();
        texs["Container"].Bind();

        projectionMat = glm::perspective(camera.m_Zoom, (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
        viewMat = camera.GetViewMatrix();
        cubeShader.SetUniformMat4("view", viewMat);
        
        for (int y = 0; y < 3; y++)
        {
            for (int z = 0; z < 16; z++)
            {
                for (int x = 0; x < 16; x++)
                {
                    //initialize
                    modelMat = glm::mat4(1.0f);

                    //configure positions
                    glm::vec3 positionInWorld = glm::vec3(0.0f - x, 0.0f - y, 0.0f - z);
                    modelMat = glm::translate(modelMat, positionInWorld);
                    //we have block positions, 
                    //send data
                    
                    cubeShader.SetUniformMat4("model", modelMat);

                    //draw

                    VAO.Bind();

                    //draw
                    //TODO: update 36 and 0 , make it depend on block rendered
                    glDrawArrays(GL_TRIANGLES, 0, 36);
                }
            }
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //#------------------Freeing memory-------------------#// 
    
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

    if (glfwGetKey(window, GLFW_KEY_SPACE))
        camera.ProcessKeyboard(Camera_Movement::UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT))
        camera.ProcessKeyboard(Camera_Movement::DOWN, deltaTime);
}

void mouse_movement_callback(GLFWwindow* window, double xposIn, double yposIn)
{
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
}

