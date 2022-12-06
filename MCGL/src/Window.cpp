#pragma once
#include "Window.h"
#include <iostream>

//#------------------Window settings-------------------#//
const unsigned int WIDTH = 1280;
const unsigned int HEIGHT = 720;


Window::Window(std::string windowName, const uint32_t WIDTH, const uint32_t HEIGHT)
{
    m_Width = WIDTH;
    m_Height = HEIGHT;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(WIDTH, HEIGHT, windowName.c_str(), nullptr, nullptr);
    

    if (!window)
    {
        std::cout << "Failed to create window\n";
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(window);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to init GLAD\n";
        exit(-1);
    }

    glViewport(0, 0, WIDTH, HEIGHT);

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int IN_WIDTH, int IN_HEIGHT) {
        glViewport(0, 0, IN_WIDTH, IN_HEIGHT);
        });
}

Window::~Window() { glfwTerminate(); }

void Window::Close() { glfwSetWindowShouldClose(window, true); }

GLFWwindow* Window::Get() { return window; }
uint32_t Window::GetWidth() { return m_Width; }
uint32_t Window::GetHeight() { return m_Height; }

bool Window::ShouldClose() { return glfwWindowShouldClose(window); };

void Window::SwapBuffers() { glfwSwapBuffers(window); }
void Window::PollEvents() { glfwPollEvents(); }
