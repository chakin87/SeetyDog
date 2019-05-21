#include "Shader.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include "SeetyDog/Logger.h"


Shader::Shader(const std::string & filepath)
{
	// TODO: Fix this hard coded filePath
	ShaderProgramSource source = ParseShader("C:/CPP/SeetyDog/DogPark/source/Breakout/Resources/Shaders/basic.shader");
	this->Compile(source.VertexSource, source.FragmentSource);
	//this->GetShader();
}

Shader & Shader::Use()
{
	glUseProgram(this->ID);
	return *this;
}

void Shader::Compile(std::string& vertexSource, std::string& fragmentSource, const char * geometrySource)
{
	GLuint sVertex, sFragment, gShader;
	const char* vs = vertexSource.c_str();
	const char* fs = fragmentSource.c_str();
	// Vertex Shader
	sVertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(sVertex, 1, &vs, NULL);
	glCompileShader(sVertex);
	checkCompileErrors(sVertex, "VERTEX");
	// Fragment Shader
	sFragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(sFragment, 1, &fs, NULL);
	glCompileShader(sFragment);
	checkCompileErrors(sFragment, "FRAGMENT");
	// If geometry shader source code is given, also compile geometry shader
	if (geometrySource != nullptr)
	{
		gShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(gShader, 1, &geometrySource, NULL);
		glCompileShader(gShader);
		checkCompileErrors(gShader, "GEOMETRY");
	}
	// Shader Program
	this->ID = glCreateProgram();
	glAttachShader(this->ID, sVertex);
	glAttachShader(this->ID, sFragment);
	if (geometrySource != nullptr)
		glAttachShader(this->ID, gShader);
	glLinkProgram(this->ID);
	checkCompileErrors(this->ID, "PROGRAM");
	// Delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(sVertex);
	glDeleteShader(sFragment);
	if (geometrySource != nullptr)
		glDeleteShader(gShader);
}

void Shader::SetFloat(const char * name, float value, bool useShader)
{
	if (useShader)
		this->Use();
	glUniform1f(glGetUniformLocation(this->ID, name), value);
}

void Shader::SetInteger(const char * name, int value, bool useShader)
{
	if (useShader)
		this->Use();
	glUniform1i(glGetUniformLocation(this->ID, name), value);
}

void Shader::SetVector2f(const char * name, float x, float y, bool useShader)
{
	if (useShader)
		this->Use();
	glUniform2f(glGetUniformLocation(this->ID, name), x, y);
}

void Shader::SetVector2f(const char * name, const glm::vec2 & value, bool useShader)
{
	if (useShader)
		this->Use();
	glUniform2f(glGetUniformLocation(this->ID, name), value.x, value.y);
}

void Shader::SetVector3f(const char * name, float x, float y, float z, bool useShader)
{
	if (useShader)
		this->Use();
	glUniform3f(glGetUniformLocation(this->ID, name), x, y, z);
}

void Shader::SetVector3f(const char * name, const glm::vec3 & value, bool useShader)
{
	if (useShader)
		this->Use();
	glUniform3f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z);
}

void Shader::SetVector4f(const char * name, float x, float y, float z, float w, bool useShader)
{
	if (useShader)
		this->Use();
	glUniform4f(glGetUniformLocation(this->ID, name), x, y, z, w);
}

void Shader::SetVector4f(const char * name, const glm::vec4 & value, bool useShader)
{
	if (useShader)
		this->Use();
	glUniform4f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z, value.w);
}

void Shader::SetMatrix4(const char * name, const glm::mat4 & matrix, bool useShader)
{
	if (useShader)
		this->Use();
	glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

ShaderProgramSource Shader::ParseShader(const std::string & filePath)
{
	SD_TRACE(filePath);
	std::ifstream stream(filePath);
	// TODO: error handeling for file open
	if (!stream.is_open()) {
		SD_TRACE("InShaderParse(vertex FILE NOT OPEN!)()()()I");

	}

	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1, GEOMETRY = 2
	};


	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while (getline(stream, line)) {

		if (line.find("#shader") != std::string::npos) {

			if (line.find("vertex") != std::string::npos) {
				//set mode to vertex
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos) {
				//set mode to fragment
				type = ShaderType::FRAGMENT;
			}
			else if (line.find("geometry") != std::string::npos) {
				//set mode to fragment
				type = ShaderType::GEOMETRY;
			}
		}
		else {
			//std::cout << "\n\nType: " << (int)type << "\n\n line:" << line;
			ss[(int)(type)] << line << '\n';
		}
	}
	return { ss[0].str(), ss[1].str() };
}

Shader Shader::GetShader()
{
	return *this;
}

void Shader::checkCompileErrors(unsigned int object, std::string type)
{
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(object, 1024, NULL, infoLog);
			std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- "
				<< std::endl;
		}
	}
	else
	{
		glGetProgramiv(object, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(object, 1024, NULL, infoLog);
			std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- "
				<< std::endl;
		}
	}
}
