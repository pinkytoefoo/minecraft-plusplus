#pragma once

#include <string>

class Shader
{
public:
    Shader(const std::string& vsFilePath, const std::string& fsFilePath);
    ~Shader();

    unsigned int CreateShaderProgram(const std::string& vsCode, const std::string& fsCode);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    void Bind();
    void Unbind();

    void SetUniform(const std::string& name, float v0, float v1, float v2, float v3);
    void SetUniform1i(const std::string& name, int value);
    int GetUniformLocation(const std::string& name);
private:
    std::string GetShaderSource(const std::string& sourceFile);
    const char* TypeToString(int type);

    unsigned int m_RendererID;
};