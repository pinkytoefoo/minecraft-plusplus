#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.hpp"

Shader::Shader(const std::string& vsFilePath, const std::string& fsFilePath)
{
    std::string vsSourceCode = getShaderSource_(vsFilePath);
    std::string fsSourceCode = getShaderSource_(fsFilePath);

    id_ = createShaderProgram(vsSourceCode, fsSourceCode);
}

Shader::~Shader()
{
    glDeleteProgram(id_);
}

unsigned int Shader::createShaderProgram(const std::string& vertexShaderCode, const std::string& fragmentShaderCode)
{
    unsigned int program = glCreateProgram();
    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderCode);
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderCode);
    
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == 0)
    {
        int infoLogLength;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);

        if (infoLogLength > 0)
        {
            char* infoLog = (char*) alloca(static_cast<size_t>(infoLogLength) * sizeof(char));
            glGetShaderInfoLog(id, infoLogLength, &infoLogLength, infoLog);

            std::cerr << typeToString_(type) << " shader compile error: " << infoLog << '\n';
        }

        glDeleteShader(id);
        // todo: return exception
        return -1;
    }

    return id;
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat)
{
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::setUniform(const std::string& name, float v0, float v1, float v2, float v3)
{
    glUniform4f(getUniformLocation(name), v0, v1, v2, v3);
}

void Shader::setUniform1i(const std::string& name, int value)
{
    glUniform1i(getUniformLocation(name), value);
}

int Shader::getUniformLocation(const std::string& name)
{
    auto it = uniformCache_.find(name);
    if(it != uniformCache_.end())
        return it->second;

    int location = glGetUniformLocation(id_, name.c_str());

    #ifndef NDEBUG
    if(location == -1)
        std::cout << "Uniform '" << name << "' not found\n";
    #endif

    uniformCache_[name] = location;

    return location;
}

void Shader::bind()
{
    glUseProgram(id_);
}

void Shader::unbind()
{
    glUseProgram(0);
}

const char* Shader::typeToString_(int type)
{
    const char* result;
    switch(type)
    {
        case GL_VERTEX_SHADER:
            result = (const char*)"Vertex";
            break;
        case GL_FRAGMENT_SHADER:
            result = (const char*)"Fragment";
            break;
    }

    return result;
}

std::string Shader::getShaderSource_(const std::string& sourceFile)
{
    std::ifstream stream(sourceFile);

    std::string line;
    std::stringstream ss;
    while(getline(stream, line))
    {
        ss << line << '\n';
    }
    // std::cout << ss.str() << '\n';
    return ss.str();
}

