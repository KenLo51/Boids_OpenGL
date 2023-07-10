#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <stdlib.h>
#include <string>
#include <fstream>
#include <iostream>
#include <map>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// shader base class
class ShaderBase {
// variables
private:
protected:
	// store loaded Shaders, to prevent reload the same shaders
	std::map <std::string, GLuint> loadedShaders;
public:
	// Program ID
	GLuint ID;

// functions
protected:
	// read all contents from file
	std::string GetFileContents(const char* filename);

public:
	// Constructors
	ShaderBase();
	// Copy constructor
	ShaderBase(const ShaderBase&);
	// Destructor
	~ShaderBase();

	// read and complie shader
	GLuint ShaderSource(const char* shaderFile, GLenum shaderType);
	// delete all loaded shader
	void ClearShaderCache();
	// delete a loaded shader
	void RemoveShader(const char* fileName);
	// use shader
	void Activate();

	// utility uniform functions
	void setUniform(const char* name, bool const value) {
		glUniform1i(glGetUniformLocation(ID, name), int(value));
	}
	void setUniform(const char* name, int const value) {
		glUniform1i(glGetUniformLocation(ID, name), value);
	}
	void setUniform(const char* name, unsigned int const value) {
		glUniform1ui(glGetUniformLocation(ID, name), value);
	}
	void setUniform(const char* name, float const value) {
		glUniform1f(glGetUniformLocation(ID, name), value);
	}
	void setUniform(const char* name, glm::vec2& value) {
		glUniform2fv(glGetUniformLocation(ID, name), 1, glm::value_ptr(value));
	}
	void setUniform(const char* name, glm::ivec2& value) {
		glUniform2iv(glGetUniformLocation(ID, name), 1, glm::value_ptr(value));
	}
	void setUniform(const char* name, glm::vec3& value) {
		glUniform3fv(glGetUniformLocation(ID, name), 1, glm::value_ptr(value));
	}
	void setUniform(const char* name, glm::vec4& value) {
		glUniform4fv(glGetUniformLocation(ID, name), 1, glm::value_ptr(value));
	}
	void setUniform(const char* name, glm::mat3& value) {
		glUniformMatrix3fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(value));
	}
	void setUniform(const char* name, glm::mat4& value) {
		glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(value));
	}

	void setUniform(const GLint location, bool const value) {
		glUniform1i(location, int(value));
	}
	void setUniform(const GLint location, int const value) {
		glUniform1i(location, value);
	}
	void setUniform(const GLint location, unsigned int const value) {
		glUniform1ui(location, value);
	}
	void setUniform(const GLint location, float const value) {
		glUniform1f(location, value);
	}
	void setUniform(const GLint location, glm::vec2& value) {
		glUniform2fv(location, 1, glm::value_ptr(value));
	}
	void setUniform(const GLint location, glm::vec3& value) {
		glUniform3fv(location, 1, glm::value_ptr(value));
	}
	void setUniform(const GLint location, glm::vec4& value) {
		glUniform4fv(location, 1, glm::value_ptr(value));
	}
	void setUniform(const GLint location, glm::mat3& value) {
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}
	void setUniform(const GLint location, glm::mat4& value) {
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

};

// normal shader class for render
class Shader : public ShaderBase {
// variables
private:
protected:
public:
	GLuint vertexShader_ID;
	GLuint tessContShader_ID;
	GLuint tessEvalShader_ID;
	GLuint geometryShader_ID;
	GLuint fragmentShader_ID;

// functions
protected:
public:
	// Constructors
	Shader();
	Shader(const char* vertexFile, const char* fragmentFile);
	Shader(const char* vertexFile, const char* tessCtrlFile, const char* tessEvalFile, const char* geometryFile, const char* fragmentFile);
	
	// Copy constructor
	Shader(const Shader&);
	// Destructor, delete program only (does not delete shaders)
	~Shader();

	// update shaders
	void UpdateSource(const char* vertexFile, const char* tessCtrlFile, const char* tessEvalFile, const char* geometryFile, const char* fragmentFile);
	// delete shaders and program
	void Delete();

};

// compute shader class
class ComputeShader : public ShaderBase {
	// variables
private:
protected:
public:
	GLuint computeShader_ID;

	// functions
protected:
public:

};
#endif