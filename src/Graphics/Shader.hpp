#pragma once

#include <string>

#include <glm/glm.hpp>

class Shader
{
public:
    Shader(const std::string& vsFilePath, const std::string& fsFilePath);
    ~Shader();

    unsigned int createShaderProgram(const std::string& vsCode, const std::string& fsCode);
    unsigned int compileShader(unsigned int type, const std::string& source);
    void bind();
    void unbind();

    void setMat4(const std::string& name, const glm::mat4& mat);
    void setUniform(const std::string& name, float v0, float v1, float v2, float v3);
    void setUniform1i(const std::string& name, int value);
    int getUniformLocation(const std::string& name);

private:
    std::string getShaderSource_(const std::string& sourceFile);
    const char* typeToString_(int type);
    
    std::unordered_map<std::string, int> uniformCache_;
    unsigned int id_;
};
