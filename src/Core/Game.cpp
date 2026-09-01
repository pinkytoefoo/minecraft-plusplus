#include <iostream>
#include <vector>
#include <string>

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Game.hpp"
#include "Util.hpp"
#include "Graphics/VertexArray.hpp"
#include "Graphics/VertexBuffer.hpp"
#include "Graphics/IndexBuffer.hpp"
#include "Graphics/Shader.hpp"
#include "Graphics/Texture.hpp"

// TODO: abstract
// TODO: render over imgui dock
void GLDebugMessageCallback(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message, const void *userParam)
{
    std::cout << message << '\n';
}

Game::Game()
    : m_Window(1280, 720, "Minecraft++")
{
    ASSERT_INIT(m_Window.Init());
    
    glfwMakeContextCurrent(m_Window.GetWindow());
    
    ASSERT_INIT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(GLDebugMessageCallback, this);
    glfwSetFramebufferSizeCallback(m_Window.GetWindow(), [](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    });

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(m_Window.GetWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

Game::~Game()
{
    std::cout << "Destroying Game ...\n";
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    
    glfwTerminate();
}

void Game::Run()
{
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,    0.0f, 0.0f,  // Bottom Left
        0.5f, -0.5f, 0.0f,     1.0f, 0.0f,  // Bottom Right
        0.5f, 0.5f, 0.0f,      1.0f, 1.0f,   // Top Right
        -0.5f, 0.5f, 0.0f,     0.0f, 1.0f  // Top Left
    };

    // float positions[] = {
    //     -0.5f, 0.5f, 0.0f,
    //     -0.5f, -0.5f, 0.0f,
    //     0.5f, -0.5f, 0.0f,
    //     0.5f, 0.5f, 0.0f
    // };

    unsigned int indices[] = {
        0, 1, 2,
        0, 3, 2
    };

    VertexArray vao;
    vao.Bind();
    // vbo already binded at construction
    VertexBuffer vbo(20 * sizeof(float), vertices);
    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, false, 5 * sizeof(float), 0);
    vao.LinkAttrib(vbo, 1, 2, GL_FLOAT, false, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    // unbind vbo and vao

    IndexBuffer ibo(6 * sizeof(unsigned int), indices);
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    ImVec4 triColor = ImVec4(0.8f, 0.3f, 0.5f, 1.0f);

    Shader shader("../assets/shaders/ttest.vert", "../assets/shaders/ttest.frag");
    shader.Bind();

    Texture texture("../assets/textures/dirt.png");
    texture.Bind();

    // Rebind vao and ibo
    vao.Bind();
    ibo.Bind();

    ImGuiIO& io = ImGui::GetIO(); (void)io;

    while(!glfwWindowShouldClose(m_Window.GetWindow())) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        // shader.SetUniform("triColor", triColor.x, triColor.y, triColor.z, triColor.w);
        texture.Bind();
        shader.Bind();
        vao.Bind();
        glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_INT, 0);

        // - GUI -
        ImGui::Begin("Configurer");

        ImGui::ColorEdit3("clear color", (float*)&clear_color);
        ImGui::ColorEdit3("triangle color", (float*)&triColor);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::End();
        // - GUI -
        
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(m_Window.GetWindow());
    }
}
