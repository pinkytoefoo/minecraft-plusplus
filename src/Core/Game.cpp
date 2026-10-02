#include <string>
#include <array>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
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
    while(m_Window.PollEvent(event))
    {
        std::visit(Overloaded {
            [&](const KeyEvent& e) {
                if(e.action == GLFW_REPEAT)
                    return;
                
                if (e.key >= 0 && e.key < GLFW_KEY_LAST)
                    m_Keys[static_cast<std::size_t>(e.key)] = e.action;
            },
            [&](const MouseMoveEvent& e) {

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
    if (m_Keys[GLFW_KEY_W])
        m_Camera.ProcessKeyboard(CameraDirection::FORWARD, dt);
    if (m_Keys[GLFW_KEY_S])
        m_Camera.ProcessKeyboard(CameraDirection::BACKWARD, dt);
    if (m_Keys[GLFW_KEY_A])
        m_Camera.ProcessKeyboard(CameraDirection::LEFT, dt);
    if (m_Keys[GLFW_KEY_D])
        m_Camera.ProcessKeyboard(CameraDirection::RIGHT, dt);
}

Game::Game()
    : m_Window{1024, 1024, "Minecraft++"}
    , m_Camera{static_cast<float>(m_Window.GetWidth()) / m_Window.GetHeight()}
    , m_GuiContext{m_Window.NativeHandle()}
{
    #ifndef NDEBUG
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(GLDebugMessageCallback, this);
    #endif

    glEnable(GL_CULL_FACE);
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
    // 2. Setup VAO layouts via DSA (Zero global state side-effects)
    VertexArray vao;
    
    unsigned int currentAttrib{0};
    unsigned int posCount{3};
    // Attribute 0: Positions (3 floats)
    vao.LinkAttribute(currentAttrib++, 0, posCount, GL_FLOAT, GL_FALSE, 0); 
    // Attribute 1: UVs (2 floats)
    vao.LinkAttribute(currentAttrib++, 0, 2, GL_FLOAT, GL_FALSE, posCount * sizeof(float)); 

    vao.BindVertexBuffer(0, vbo.GetId(), 0, 5 * sizeof(float));

    vao.BindIndexBuffer(ibo.GetId());

    Shader shader("assets/shaders/ttest.vert", "assets/shaders/ttest.frag");
    shader.Bind();

    Texture texture("assets/textures/dirt.png");
    texture.Bind();

    double deltaTime = 0.0f;
    double lastFrame = 0.0f;

    while(m_Window.IsRunning()) {
        double currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();
        ProcessEvents_();

        ProcessInputs_(deltaTime);

        ImVec4 clear_color = m_Gui.GetClearColor();

        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // texture.Bind();
        // shader.Bind();
        vao.Bind();

        model = glm::rotate(model, static_cast<float>(1.0f * deltaTime), glm::vec3(0.0f, 1.0f, 0.0f));
        view = m_Camera.GetViewMatrix();
        projection = m_Camera.GetProjectionMatrix();
        
        shader.SetMat4("transform", projection * view * model);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        
        m_GuiContext.StartFrame();
        m_Gui.OnUpdate();
        m_GuiContext.EndFrame();
        
        m_Window.SwapBuffers();
    }
}
