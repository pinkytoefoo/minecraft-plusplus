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
    std::string vsSourceCode = GetShaderSource(vsFilePath);
    std::string fsSourceCode = GetShaderSource(fsFilePath);

    m_RendererID = CreateShaderProgram(vsSourceCode, fsSourceCode);
}

Shader::~Shader()
{
    glDeleteProgram(m_RendererID);
}

unsigned int Shader::CreateShaderProgram(const std::string& vertexShaderCode, const std::string& fragmentShaderCode)
{
    unsigned int program = glCreateProgram();
    unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderCode);
    unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderCode);
    
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
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
            char* infoLog = (char*) alloca(infoLogLength * sizeof(char));
            glGetShaderInfoLog(id, infoLogLength, &infoLogLength, infoLog);

            std::cerr << TypeToString(type) << " shader compile error: " << infoLog << '\n';
        }

        glDeleteShader(id);
        // todo: return exception
        return -1;
    }

    return id;
}

void Shader::SetMat4(const std::string& name, const glm::mat4& mat)
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::SetUniform(const std::string& name, float v0, float v1, float v2, float v3)
{
    glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniform1i(const std::string& name, int value)
{
    glUniform1i(GetUniformLocation(name), value);
}

int Shader::GetUniformLocation(const std::string& name)
{
    auto it = m_UniformCache.find(name);
    if(it != m_UniformCache.end())
        return it->second;

    int location = glGetUniformLocation(m_RendererID, name.c_str());

    #ifndef NDEBUG
    if(location == -1)
        std::cout << "Uniform '" << name << "' not found\n";
    #endif

    m_UniformCache[name] = location;

    return location;
}

void Shader::Bind()
{
    glUseProgram(m_RendererID);
}

void Shader::Unbind()
{
    glUseProgram(0);
}

const char* Shader::TypeToString(int type)
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

std::string Shader::GetShaderSource(const std::string& sourceFile)
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

