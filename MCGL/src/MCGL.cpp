#include "MCGL.h"

#define WIDTH  1280
#define HEIGHT 720

//#------------------Camera---------------------#//
Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));
float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;
bool firstMouse = true;

//#------------------Timings---------------------#//
float deltaTime = 0.0f;
float lastFrame = 0.0f;

double lastTime = 0;
int nbFrames = 0;

void showFPS(GLFWwindow* pWindow)
{
    double currentTime = glfwGetTime();
    double delta = currentTime - lastTime;

    nbFrames++;
    if (delta >= 1.0)
    {
        double fps = double(nbFrames) / delta;

        std::stringstream ss;
        ss << "FPS: " << fps;
        
        glfwSetWindowTitle(pWindow, ss.str().c_str());

        nbFrames = 0;
        lastTime = currentTime;
    }
}

void mouseMovementCallback(GLFWwindow* window, double xposIn, double yposIn)
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
    float yoffset = lastY - ypos; //y goes from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

MCGL::MCGL(): window("MCGL", 1280, 720)
{
    glfwSetInputMode(window.Get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window.Get(), mouseMovementCallback);
}

MCGL::~MCGL()
{
    glfwTerminate();
}

void MCGL::Run()
{
    Shader cubeShader("C:\\Dev\\OpenGL\\MCGL\\MCGL\\res\\shaders\\shader.glsl");
    cubeShader.Use();

    Chunk c { 0,0 };
    c.Update();

    std::vector<GLbyte> data = c.RetrieveData();
    
    //std::ranges::copy(data1, std::back_inserter(data));
    VertexArray va;
    VertexBuffer chunkDataBuffer(&data[0], data.size() * sizeof(char));
    VertexBufferLayout blockDataLayout;
    
    blockDataLayout.PushElementByte(3, false);
    blockDataLayout.PushElementByte(2, false);

    va.AddBuffer(chunkDataBuffer, blockDataLayout);

    //#------------------Textures-------------------#// 
    Texture blockTex("C:\\Dev\\OpenGL\\MCGL\\MCGL\\res\\textures\\blocks\\tilemap.png");
    
    blockTex.Bind();

    cubeShader.SetUniform1i("texture1", 0);

    //#------------------Transformations-------------------#//
    glm::mat4 viewMat, projectionMat, modelMat;
    modelMat = projectionMat = glm::mat4(1.0f);

    projectionMat = glm::perspective(glm::radians(60.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 200.0f);
    cubeShader.SetUniformMat4("projection", projectionMat);

    modelMat = glm::translate(modelMat, glm::vec3(0,0,0));
    cubeShader.SetUniformMat4("model", modelMat);

    //#------------------Additional Configuration-------------------#// 
    glEnable(GL_DEPTH_TEST);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!window.ShouldClose())
    {
        {
            double currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;
        }

        showFPS(window.Get());
        ProcessInput();
        
        glm::vec3 clearColor = glm::normalize(glm::vec3(0, 230, 240));
        glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cubeShader.Use();
        va.Bind();
        viewMat = camera.GetViewMatrix();
        cubeShader.SetUniformMat4("view", viewMat);

        c.Render(va, cubeShader);

        window.SwapBuffers();
        window.PollEvents();
    }

}

void MCGL::ProcessInput()
{
    if (glfwGetKey(window.Get(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window.Get(), true);

    if (glfwGetKey(window.Get(), GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
    if (glfwGetKey(window.Get(), GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);

    if (glfwGetKey(window.Get(), GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
    if (glfwGetKey(window.Get(), GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);

    if (glfwGetKey(window.Get(), GLFW_KEY_SPACE))
        camera.ProcessKeyboard(Camera_Movement::UP, deltaTime);
    if (glfwGetKey(window.Get(), GLFW_KEY_LEFT_SHIFT))
        camera.ProcessKeyboard(Camera_Movement::DOWN, deltaTime);
    
}

