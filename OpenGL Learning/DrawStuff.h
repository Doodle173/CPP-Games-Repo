#include<GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include<string>
#include<sstream>

#define ASSERT(x) if(!(x)) __debugbreak();
#define GlCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))


static void GLClearError() {
	while (glGetError() != GL_NO_ERROR) {

	}
}

static bool GLLogCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		std::cout << "[OpenGL Error]: (" << error << ")\n" << "\n@ function: \n"<< function << "\n" << "\n@ file & line number:\n" << file << ":" << line << std::endl;
		return false;
	}
	return true;
}

struct ShaderProgramSource {
	std::string VertexSource; 
	std::string FragmentSource;
};
static ShaderProgramSource ParseShader(const std::string& filepath) {
	std::ifstream stream(filepath);

	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];

	ShaderType type;
	while (getline(stream,line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos) {
				//set mode to vertex
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos) {
				//set mode to fragment
				type = ShaderType::FRAGMENT;
			}
		}
		else {
			ss[(int)type] << line << "\n";
		}
	}
	return { ss[0].str(), ss[1].str() };
}

static unsigned int CompileShader(unsigned int type, const std::string& source) {
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)_malloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Shader failed to compile" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}
static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
	unsigned int program = glCreateProgram();
	unsigned int vertShader = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fragShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

	return program;
}

void setupTriangle() {
	float vertex[12] = {
		//x   //y
	   -0.5f, -0.5f, //index 0
		0.5f, -0.5f, //index 1
		0.5f, 0.5f,  //index 2
		-0.5f, 0.5f, //index 3
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};
	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), vertex, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	unsigned int ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);


	//std::cout << "Vertex Shader:"<< std::endl;
	//std::cout << source.VertexSource << std::endl;

	//std::cout << "Fragment Shader:" << std::endl;
	//std::cout << source.FragmentSource << std::endl;

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void drawTriangle() {
	GlCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
}
