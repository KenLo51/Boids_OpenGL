#include "ShaderClass.h"

// shader base class
// 
// read all contents from file
std::string ShaderBase::GetFileContents(const char* filename) {
	std::ifstream ifs(filename, std::ifstream::in);
	if (!ifs.good()) {
		std::cout << "ERROR::SHADER::OPENING FILE \n" << filename << std::endl;
		exit(1);
	}

	std::string fileContents;
	// getting file size
	ifs.seekg(0, std::ios_base::end);
	fileContents.resize(ifs.tellg());
	// reading file content
	ifs.seekg(0, std::ios_base::beg);
	ifs.read(&fileContents[0], fileContents.size());
	// close file
	ifs.close();

	return fileContents;
}

// Constructors
ShaderBase::ShaderBase() {
	ID = glCreateProgram();
}
// Copy constructor
ShaderBase::ShaderBase(const ShaderBase& t) {
	ID = glCreateProgram();
}
// Destructor
ShaderBase::~ShaderBase() {
	if (ID) glDeleteProgram(ID);
}

// read and complie shader
GLuint ShaderBase::ShaderSource(const char* shaderFile, GLenum shaderType) {
	if (shaderFile == NULL)
		return 0;

	std::cout << "[INFO::SHADER::LOAD] " << shaderFile << std::endl;

	// if hader has been loaded(compiled)
	if (loadedShaders.count(shaderFile) > 0) {
		std::cout << "[INFO::SHADER::LOAD] Found shader in previes loaded shaders" << std::endl;
		return loadedShaders[shaderFile];
	}
	else {
		std::cout << "[INFO::SHADER::LOAD] Load and compile new shader" << std::endl;
		// load and compile new shader
		// read shader file content
		std::string vertexShaderSource = GetFileContents(shaderFile);
		// create vertex shader
		GLuint shader_ID = glCreateShader(shaderType);
		if (shader_ID == 0) {
			std::cout << "[ERROR::SHADER] Can not create shader\n" << std::endl;
			exit(1);
		}

		// put shader code to opengl
		const char* vertexShaderSourcePtr = vertexShaderSource.c_str();
		glShaderSource(shader_ID, 1, &vertexShaderSourcePtr, NULL);

		// compile Vertex Shader
		glCompileShader(shader_ID);

		// check if compile success
		GLint success;
		glGetShaderiv(shader_ID, GL_COMPILE_STATUS, &success);
		if (!success) {
			char infoLog[512];
			glGetShaderInfoLog(shader_ID, sizeof(infoLog), NULL, infoLog);
			std::cout << "[ERROR::SHADER] Compilation failed\n" << infoLog << std::endl;
			exit(1);
		}

		// add to cache
		loadedShaders.insert(std::pair<std::string, GLuint>(std::string(shaderFile), shader_ID));
		return shader_ID;
	}
	return 0;
}
// delete all loaded shader
void ShaderBase::ClearShaderCache() {
	for (const std::pair<std::string, GLuint>& loadedShader : loadedShaders) {
		glDeleteShader(loadedShader.second);
	}
	loadedShaders.clear();
}

// delete a loaded shader
void ShaderBase::RemoveShader(const char* fileName) {
	glDeleteShader(loadedShaders[fileName]);
	loadedShaders.erase(fileName);
}
// use shader
void ShaderBase::Activate() {
	glUseProgram(ID);
}

// normal shader class for render
// Constructors
Shader::Shader() : ShaderBase() {
	vertexShader_ID = 0;
	tessContShader_ID = 0;
	tessEvalShader_ID = 0;
	geometryShader_ID = 0;
	fragmentShader_ID = 0;
}
Shader::Shader(const char* vertexFile, const char* fragmentFile) : ShaderBase() {
	UpdateSource(vertexFile, NULL, NULL, NULL, fragmentFile);
}
Shader::Shader(const char* vertexFile, const char* tessCtrlFile, const char* tessEvalFile, const char* geometryFile, const char* fragmentFile) : ShaderBase() {
	UpdateSource(vertexFile, tessCtrlFile, tessEvalFile, geometryFile, fragmentFile);
}
// Copy constructor
Shader::Shader(const Shader& t) : ShaderBase() {
	if (vertexShader_ID = t.vertexShader_ID) glAttachShader(ID, vertexShader_ID);
	if(tessContShader_ID = t.tessContShader_ID) glAttachShader(ID, tessContShader_ID);
	if(tessEvalShader_ID = t.tessEvalShader_ID) glAttachShader(ID, tessEvalShader_ID);
	if(geometryShader_ID = t.geometryShader_ID) glAttachShader(ID, geometryShader_ID);
	if(fragmentShader_ID = t.fragmentShader_ID) glAttachShader(ID, fragmentShader_ID);

	glLinkProgram(ID);
}
// Destructor
Shader::~Shader(){
	if(ID)	glDeleteProgram(ID);
}

// update shaders
void Shader::UpdateSource(const char* vertexFile, const char* tessCtrlFile, const char* tessEvalFile, const char* geometryFile, const char* fragmentFile) {
	if (vertexFile != NULL) {
		vertexShader_ID = ShaderSource(vertexFile, GL_VERTEX_SHADER);
		glAttachShader(ID, vertexShader_ID);
	}
	else {
		if (vertexShader_ID != 0) glDetachShader(ID, vertexShader_ID);
	}

	if (tessCtrlFile != NULL) {
		tessContShader_ID = ShaderSource(tessCtrlFile, GL_TESS_CONTROL_SHADER);
		glAttachShader(ID, tessContShader_ID);
	}
	else {
		if (tessContShader_ID != 0) glDetachShader(ID, tessContShader_ID);
	}

	if (tessEvalFile != NULL) {
		tessEvalShader_ID = ShaderSource(tessEvalFile, GL_TESS_EVALUATION_SHADER);
		glAttachShader(ID, tessEvalShader_ID);
	}
	else {
		if (tessEvalShader_ID != 0) glDetachShader(ID, tessEvalShader_ID);
	}

	if (geometryFile != NULL) {
		geometryShader_ID = ShaderSource(geometryFile, GL_GEOMETRY_SHADER);
		glAttachShader(ID, geometryShader_ID);
	}
	else {
		if (geometryShader_ID != 0) glDetachShader(ID, geometryShader_ID);
	}

	if (fragmentFile != NULL) {
		fragmentShader_ID = ShaderSource(fragmentFile, GL_FRAGMENT_SHADER);
		glAttachShader(ID, fragmentShader_ID);
	}
	else {
		if (fragmentShader_ID != 0) glDetachShader(ID, fragmentShader_ID);
	}

	glLinkProgram(ID);
	// check if link success
	GLint success;
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[1024];
		glGetProgramInfoLog(ID, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		exit(1);
	}
}
// delete shaders
void Shader::Delete() {
	if (vertexShader_ID) glDeleteShader(vertexShader_ID);
	if (tessContShader_ID) glDeleteShader(tessContShader_ID);
	if (tessEvalShader_ID) glDeleteShader(tessEvalShader_ID);
	if (geometryShader_ID) glDeleteShader(geometryShader_ID);
	if (fragmentShader_ID) glDeleteShader(fragmentShader_ID);
	for (const std::pair<std::string, GLuint>& loadedShader : loadedShaders) {
		if (loadedShader.second == vertexShader_ID ||
			loadedShader.second == tessContShader_ID ||
			loadedShader.second == tessEvalShader_ID ||
			loadedShader.second == geometryShader_ID ||
			loadedShader.second == fragmentShader_ID) {
			loadedShaders.erase(loadedShader.first);
		}
	}
}