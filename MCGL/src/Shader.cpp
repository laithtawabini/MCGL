#include "shader.h"


void Shader::createProgram(const ShaderSource& src)
{
	unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);

	const char* vsString = src.vertexShader.c_str();
	const char* fsString = src.fragmentShader.c_str();

	glShaderSource(vs, 1, &vsString, nullptr);
	glShaderSource(fs, 1, &fsString, nullptr);

	glCompileShader(vs);

	int success;
	glGetShaderiv(vs, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		int length;
		glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &length);

		char* infoLog = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(vs, length, nullptr, infoLog);

		std::cout << "Error compiling vertex shader: " << infoLog << std::endl;
		exit(-1);
	}

	glCompileShader(fs);

	glGetShaderiv(fs, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		int length;
		glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &length);

		char* infoLog = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(fs, length, nullptr, infoLog);

		std::cout << "Error compiling fragment shader: " << infoLog << std::endl;
		exit(-1);
	}

	unsigned int program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);

	glGetProgramiv(fs, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		int length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

		char* infoLog = (char*)alloca(length * sizeof(char));
		glGetProgramInfoLog(program, length, nullptr, infoLog);

		std::cout << "Error linking program: " << infoLog << std::endl;
		exit(-1);
	}

	this->ID = program;
	glDeleteShader(vs);
	glDeleteShader(fs);
}

ShaderSource Shader::parseFile(const std::string& filePath)
{
	std::ifstream stream(filePath);
	enum class mode {
		NONE = -1, VERTEX = 0, FRAGMENT = 1,
	};
	std::string line;
	std::stringstream ss[2];
	mode type = mode::NONE;

	while (std::getline(stream, line))
	{
		//invalid stream pos
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = mode::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = mode::FRAGMENT;
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };
}