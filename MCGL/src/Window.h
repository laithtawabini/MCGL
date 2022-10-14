#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>


class Window
{
public:
	Window(std::string, const uint32_t, const uint32_t);
	~Window();

	void Close();

	uint32_t GetHeight();
	uint32_t GetWidth();
	bool ShouldClose();

	void SwapBuffers();
	void PollEvents();

	GLFWwindow* Get();
	
public:
	GLFWwindow* window;
	uint32_t m_Width;
	uint32_t m_Height;
};