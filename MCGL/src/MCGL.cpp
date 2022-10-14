#include "MCGL.h"

#define WIDTH  1280
#define HEIGHT 720

//#------------------Camera---------------------#//
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;
bool firstMouse = true;

//#------------------Timings---------------------#//
float deltaTime = 0.0f;
float lastFrame = 0.0f;

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
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

MCGL::MCGL(): window("MCGL", 1280, 720)
{
    glfwSetInputMode(window.Get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //called when cursor is moved
    glfwSetCursorPosCallback(window.Get(), mouseMovementCallback);
}

MCGL::~MCGL()
{
    glfwTerminate();
}

void MCGL::Run()
{
    //setting up the renderer
    Shader cubeShader("C:\\Dev\\OpenGL\\MCGL\\MCGL\\res\\shaders\\shader.glsl");
    cubeShader.Use();

    //#------------------Shaders and Coordinates/shapes to be rendered-------------------#// 
    Cube cube;
    VertexArray VAO;
    VertexBuffer VBO(&(cube.getVertices()[0]), cube.getSizeOfData());
    VertexBufferLayout layout;

    layout.PushElement(GL_FLOAT, 3);
    layout.PushElement(GL_FLOAT, 2);

    VAO.AddBuffer(VBO, layout);

    CubeRenderer cubeRenderer(VAO, cubeShader);
    
    //#------------------Textures-------------------#// 
    Texture blockTex("C:\\Dev\\OpenGL\\MCGL\\MCGL\\res\\textures\\blocks\\grass_block.png");
    
    blockTex.Bind();
    cubeShader.SetUniform1i("texture1", 0);

    //#------------------Transformations-------------------#//
    glm::mat4 viewMat, projectionMat = glm::mat4(1.0f);

    projectionMat = glm::perspective(glm::radians(60.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
    cubeShader.SetUniformMat4("projection", projectionMat);

    //#------------------Additional Configuration-------------------#// 
    glEnable(GL_DEPTH_TEST);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    while (!window.ShouldClose())
    {
        {
            float currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;
        }

        ProcessInput();

        glm::vec3 clearColor = glm::normalize(glm::vec3(0, 230, 240));
        glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cubeShader.Use();
        viewMat = camera.GetViewMatrix();
        cubeShader.SetUniformMat4("view", viewMat);

        for (int y = 0; y < 3; y++)
            for (int z = 0; z < 16; z++)
                for (int x = 0; x < 16; x++)
                    cubeRenderer.DrawCube(glm::vec3(0.0f - x, 0.0f - y, 0.0f - z), blockTex);
        
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

