#include <iostream>
#include <vector>
#include <string>
#include <array>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
    : m_Window{1024, 1024, "Minecraft++"}
    , m_Camera{static_cast<float>(m_Window.GetWidth()) / m_Window.GetHeight()}
{
    m_Window.SetFramebufferCallback([this](int width, int height) {
        m_Camera.SetAspectRatio(static_cast<float>(width)/height);
        Render_();
    });

    #ifndef NDEBUG
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(GLDebugMessageCallback, this);
    #endif

    glEnable(GL_CULL_FACE);

    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();
    io.Fonts->Clear();
    io.Fonts->AddFontFromFileTTF("assets/fonts/Minecraft-Regular.ttf", 24.0f);

    ImGui_ImplGlfw_InitForOpenGL(m_Window.GetWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 430");
}

Game::~Game()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Game::Render_()
{

}

void Game::Run()
{
    constexpr auto vertices = std::array{
        // front
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,

        // back
        0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f, 1.0f,

        // left
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,

        // right
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f, 1.0f,

        // top
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,

        // bottom
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f,
    };

    constexpr auto indices = std::array{
        // front
        0u,  1u,  2u,
        0u,  2u,  3u,

        // back
        4u,  5u,  6u,
        4u,  6u,  7u,

        // left
        8u,  9u, 10u,
        8u, 10u, 11u,

        // right
        12u, 13u, 14u,
        12u, 14u, 15u,

        // top
        16u, 17u, 18u,
        16u, 18u, 19u,

        // bottom
        20u, 21u, 22u,
        20u, 22u, 23u,
    };

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
    glm::mat4 projection = glm::perspective(glm::radians(90.0f), static_cast<float>(m_Window.GetWidth()) / m_Window.GetHeight(), 0.1f, 100.0f);

    const GLubyte* vendor    = glGetString(GL_VENDOR);
    const GLubyte* renderer  = glGetString(GL_RENDERER);
    const GLubyte* version   = glGetString(GL_VERSION);

    VertexArray vao;
    vao.Bind();
    // vbo already binded at construction
    VertexBuffer vbo(vertices.size() * sizeof(float), vertices.data());
    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, false, 5 * sizeof(float), 0);
    vao.LinkAttrib(vbo, 1, 2, GL_FLOAT, false, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    IndexBuffer ibo(indices.size() * sizeof(unsigned int), indices.data());
    ImVec4 clear_color = ImVec4(0.2f, 0.5f, 0.7f, 1.0f);
    ImVec4 triColor = ImVec4(0.8f, 0.3f, 0.5f, 1.0f);

    Shader shader("assets/shaders/ttest.vert", "assets/shaders/ttest.frag");
    shader.Bind();

    Texture texture("assets/textures/dirt.png");
    texture.Bind();

    ImGuiIO& io = ImGui::GetIO(); (void)io;

    glEnable(GL_DEPTH_TEST);

    double deltaTime = 0.0f;
    double lastFrame = 0.0f;
    float lastX, lastY;
    while(!glfwWindowShouldClose(m_Window.GetWindow())) {
        double currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();

       if (glfwGetKey(m_Window.GetWindow(), GLFW_KEY_W) == GLFW_PRESS)
            m_Camera.ProcessKeyboard(CameraDirection::FORWARD, deltaTime);
        if (glfwGetKey(m_Window.GetWindow(), GLFW_KEY_S) == GLFW_PRESS)
            m_Camera.ProcessKeyboard(CameraDirection::BACKWARD, deltaTime);
        if (glfwGetKey(m_Window.GetWindow(), GLFW_KEY_A) == GLFW_PRESS)
            m_Camera.ProcessKeyboard(CameraDirection::LEFT, deltaTime);
        if (glfwGetKey(m_Window.GetWindow(), GLFW_KEY_D) == GLFW_PRESS)
            m_Camera.ProcessKeyboard(CameraDirection::RIGHT, deltaTime);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // shader.SetUniform("triColor", triColor.x, triColor.y, triColor.z, triColor.w);
        texture.Bind();
        shader.Bind();
        vao.Bind();
        model = glm::rotate(glm::mat4(1.0f), glm::radians(25.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, static_cast<float>(glfwGetTime()), glm::vec3(0.0f, 1.0f, 0.0f));
        view = m_Camera.GetViewMatrix();
        projection = m_Camera.GetProjectionMatrix();
        // model = glm::rotate(model, rotationAngle.y, glm::vec3(1.0f, 0.0f, 0.0f));
        int location = shader.GetUniformLocation("transform");
        glm::mat4 transform = projection * view * model;
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(transform));
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

        // - GUI -
        ImGui::Begin("Configurer");
        ImGui::ColorEdit3("clear color", (float*)&clear_color);
        ImGui::ColorEdit3("triangle color", (float*)&triColor);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::Spacing();

        if (ImGui::CollapsingHeader("System Diagnostics"))
        {
            ImGui::Spacing();
            ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(12.0f, 4.0f));

            if (ImGui::BeginTable("SystemInfoTable", 2)) 
            {
                ImGui::TableSetupColumn("Key", ImGuiTableColumnFlags_WidthFixed, 100.0f);
                ImGui::TableSetupColumn("Value", ImGuiTableColumnFlags_WidthStretch);

                ImGui::TableNextRow();
                ImGui::TableNextColumn(); ImGui::Text("Vendor:");
                ImGui::TableNextColumn(); ImGui::Text("%s", vendor);

                ImGui::TableNextRow();
                ImGui::TableNextColumn(); ImGui::Text("Renderer:");
                ImGui::TableNextColumn(); ImGui::Text("%s", renderer);

                ImGui::TableNextRow();
                ImGui::TableNextColumn(); ImGui::Separator();
                ImGui::TableNextColumn(); ImGui::Separator();

                ImGui::TableNextRow();
                ImGui::TableNextColumn(); ImGui::Text("Version:");
                ImGui::TableNextColumn(); ImGui::Text("%s", version);

                ImGui::EndTable();
            }

            ImGui::PopStyleVar();

            ImGui::Spacing();
            ImGui::Separator();
        }
        ImGui::End();
        // - GUI -
        
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(m_Window.GetWindow());
    }
}
