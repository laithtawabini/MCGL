#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <malloc.h>
struct ShaderSource {
	std::string vertexShader;
	std::string fragmentShader;
};

class Shader {
public:
	unsigned int ID;

	Shader(const std::string& filePath) { createProgram(parseFile(filePath)); }
	void use() { glUseProgram(ID); }
private:
	ShaderSource parseFile(const std::string& filePath);
	void createProgram(const ShaderSource&);
};


