#pragma once
#include <glad/glad.h>
#include "../vendor/glm/glm.hpp"
#include "../vendor/glm/gtc/type_ptr.hpp"
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

	Shader(const std::string& filePath) { CreateProgram(ParseFile(filePath)); }
	
	void Use() { glUseProgram(ID); }

	uint32_t GetUniformLocation(const std::string&);
	void SetUniform1i(const std::string&, const int);
	void SetUniformMat4(const std::string&, glm::mat4&);
private:
	ShaderSource ParseFile(const std::string& filePath);
	void CreateProgram(const ShaderSource&);
};


