#include <iostream>
#include <vector>
#include <string>
#include <array>

#include <glad/glad.h>
#include <glfw/glfw3.h>
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

glm::vec2 rotationAngle{0.0f, 0.0f};

// TODO: abstract
// TODO: render over imgui dock
void GLDebugMessageCallback(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message, const void *userParam)
{
    std::cout << message << '\n';
}

void ProcessInput(GLFWwindow* window, float deltaTime) {
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        rotationAngle.x -= glm::radians(90.0f) * deltaTime;
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        rotationAngle.x += glm::radians(90.0f) * deltaTime;
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        rotationAngle.y -= glm::radians(90.0f) * deltaTime;
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        rotationAngle.y += glm::radians(90.0f) * deltaTime;
}

Game::Game()
    : m_Window(1024, 1024, "Minecraft++")
{
    ASSERT_INIT(m_Window.Init());
    
    glfwMakeContextCurrent(m_Window.GetWindow());
    
    ASSERT_INIT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(GLDebugMessageCallback, this);
    glfwSetFramebufferSizeCallback(m_Window.GetWindow(), [](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
        // Render_();
    });

    glfwSwapInterval(1);

    // glfwSetKeyCallback

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


    VertexArray vao;
    vao.Bind();
    // vbo already binded at construction
    VertexBuffer vbo(vertices.size() * sizeof(float), vertices.data());
    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, false, 5 * sizeof(float), 0);
    vao.LinkAttrib(vbo, 1, 2, GL_FLOAT, false, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    IndexBuffer ibo(indices.size() * sizeof(unsigned int), indices.data());
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    ImVec4 triColor = ImVec4(0.8f, 0.3f, 0.5f, 1.0f);

    Shader shader("../assets/shaders/ttest.vert", "../assets/shaders/ttest.frag");
    shader.Bind();

    Texture texture("../assets/textures/dirt.png");
    texture.Bind();

    ImGuiIO& io = ImGui::GetIO(); (void)io;

    glEnable(GL_DEPTH_TEST);

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
    glm::mat4 projection = glm::perspective(glm::radians(90.0f), static_cast<float>(m_Window.GetHeight()) / m_Window.GetWidth(), 0.1f, 100.0f);
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    while(!glfwWindowShouldClose(m_Window.GetWindow())) {
        glfwPollEvents();
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        ProcessInput(m_Window.GetWindow(), deltaTime);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // shader.SetUniform("triColor", triColor.x, triColor.y, triColor.z, triColor.w);
        texture.Bind();
        shader.Bind();
        vao.Bind();
        model = glm::rotate(glm::mat4(1.0f), glm::radians(-25.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, static_cast<float>(glfwGetTime()), glm::vec3(0.0f, 1.0f, 0.0f));
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
        ImGui::End();
        // - GUI -
        
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(m_Window.GetWindow());
    }
}
