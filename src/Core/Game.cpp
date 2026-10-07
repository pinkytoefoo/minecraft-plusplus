#include <string>
#include <array>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#define GLM_FORCE_CONSTEXPR
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Game.hpp"
#include "Event.hpp"
#include "Graphics/VertexArray.hpp"
#include "Graphics/VertexBuffer.hpp"
#include "Graphics/IndexBuffer.hpp"
#include "Graphics/Shader.hpp"
#include "Graphics/Texture.hpp"

void Game::ProcessEvents_()
{
    Event event;
    while(m_Window.GetEventFromQueue(event))
    {
        std::visit(Overloaded {
            [&](const KeyEvent& e) {
                if(e.action == GLFW_REPEAT)
                    return;
                
                if (e.key >= 0 && e.key < GLFW_KEY_LAST)
                    m_Keys[static_cast<std::size_t>(e.key)] = e.action;
            },
            [&](const MouseMoveEvent& e) {
                m_Camera.ProcessMouse(e.xpos, e.ypos);
            },
            [&](const MouseClickEvent& e) {

            },
            [&](const WindowResizeEvent& e) {
                if (e.height == 0) // avoid divide by 0 when minimized
                    return;

                m_Camera.SetAspectRatio(static_cast<float>(e.width) / e.height);
                Render_();
            },
        }, event.Data);
    }
}

void Game::ProcessInputs_(float dt)
{
    CameraDirection direction = CameraDirection::None;

    direction |= static_cast<CameraDirection>(static_cast<int>(CameraDirection::Forward)  * m_Keys[GLFW_KEY_W]);
    direction |= static_cast<CameraDirection>(static_cast<int>(CameraDirection::Backward) * m_Keys[GLFW_KEY_S]);
    direction |= static_cast<CameraDirection>(static_cast<int>(CameraDirection::Left)     * m_Keys[GLFW_KEY_A]);
    direction |= static_cast<CameraDirection>(static_cast<int>(CameraDirection::Right)    * m_Keys[GLFW_KEY_D]);
    direction |= static_cast<CameraDirection>(static_cast<int>(CameraDirection::Up)       * m_Keys[GLFW_KEY_SPACE]);
    direction |= static_cast<CameraDirection>(static_cast<int>(CameraDirection::Down)     * m_Keys[GLFW_KEY_LEFT_CONTROL]);
    
    m_Camera.ProcessKeyboard(direction, dt);
}

Game::Game()
    : m_Window{1024, 1024, "Minecraft++"}
    , m_Camera{static_cast<float>(m_Window.GetWidth()) / m_Window.GetHeight()}
    , m_GuiContext{m_Window.NativeHandle()}
{
    #ifndef NDEBUG
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    // glDebugMessageCallback(GLDebugMessageCallback, this);
    #endif

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glEnable(GL_DEPTH_TEST);

    glfwSwapInterval(1);
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

    VertexBuffer vbo(vertices.data(), vertices.size() * sizeof(float));
    IndexBuffer ibo(indices.data(), indices.size() * sizeof(unsigned int));
    VertexArray vao;
    
    unsigned int currentAttrib{0};
    unsigned int posCount{3};
    vao.LinkAttribute(0, 0, 3, GL_FLOAT, GL_FALSE, 0);
    vao.LinkAttribute(1, 0, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float));

    vao.BindVertexBuffer(0, vbo.GetId(), 0, 5 * sizeof(float));

    vao.BindIndexBuffer(ibo.GetId());

    Shader shader("assets/shaders/ttest.vert", "assets/shaders/ttest.frag");
    shader.Bind();

    Texture texture("assets/textures/dirt.png");
    texture.Bind();

    double deltaTime = 0.0f;
    double lastFrame = 0.0f;

    // "use small, composable functions" - jason turner
    constexpr auto make_blocks = [] constexpr -> std::array<glm::vec3, 16 * 16 * 16> {
        std::array<glm::vec3, 16 * 16 * 16> blocks;
        size_t n{};
        for(float i{-8.0f}; i < 8.0f; ++i) {
            for(float j{-16.0f}; j < 0.0f; ++j) {
                for(float k{-8.0f}; k < 8.0f; ++k) {
                    blocks[n++] = glm::vec3{i, j, k};
                }
            }
        }
        return blocks;
    };

    constexpr auto blocks = make_blocks();

    while(m_Window.IsRunning()) {
        double currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        m_Window.PollEvents();
        ProcessEvents_();

        ProcessInputs_(deltaTime);

        ImVec4 clear_color = m_Gui.GetClearColor();

        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // texture.Bind();
        // shader.Bind();
        vao.Bind();

        for(auto& position : blocks) {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
            view = m_Camera.GetViewMatrix();
            projection = m_Camera.GetProjectionMatrix();
            shader.SetMat4("transform", projection * view * model);
            glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
        }
        
        m_GuiContext.StartFrame();
        ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
        m_Gui.OnUpdate();
        m_GuiContext.EndFrame();
        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
        
        m_Window.SwapBuffers();
    }
}
