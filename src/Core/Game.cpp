#include <string>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glm/glm.hpp>

#include "World/Chunk.hpp"
#include "Game.hpp"
#include "Event.hpp"
#include "Graphics/Shader.hpp"
#include "Graphics/Texture.hpp"

void Game::processEvents_()
{
    Event event;
    while(window_.getEventFromQueue(event))
    {
        std::visit(Overloaded {
            [&](const KeyEvent& e) {
                if(e.action == GLFW_REPEAT)
                    return;
                
                if (e.key >= 0 && e.key < GLFW_KEY_LAST)
                    keys_[static_cast<std::size_t>(e.key)] = e.action;
            },
            [&](const MouseMoveEvent& e) {
                camera_.processMouse(e.xpos, e.ypos);
            },
            [&](const MouseClickEvent& e) {

            },
            [&](const WindowResizeEvent& e) {
                if (e.height == 0) // avoid divide by 0 when minimized
                    return;

                camera_.setAspectRatio(static_cast<float>(e.width) / e.height);
                render_();
            },
        }, event.Data);
    }
}

void Game::processInputs_(float dt)
{
    CameraDirection direction = CameraDirection::None;

    direction |= static_cast<CameraDirection>(static_cast<int>(CameraDirection::Forward)  * keys_[GLFW_KEY_W]);
    direction |= static_cast<CameraDirection>(static_cast<int>(CameraDirection::Backward) * keys_[GLFW_KEY_S]);
    direction |= static_cast<CameraDirection>(static_cast<int>(CameraDirection::Left)     * keys_[GLFW_KEY_A]);
    direction |= static_cast<CameraDirection>(static_cast<int>(CameraDirection::Right)    * keys_[GLFW_KEY_D]);
    direction |= static_cast<CameraDirection>(static_cast<int>(CameraDirection::Up)       * keys_[GLFW_KEY_SPACE]);
    direction |= static_cast<CameraDirection>(static_cast<int>(CameraDirection::Down)     * keys_[GLFW_KEY_LEFT_CONTROL]);
    
    camera_.processKeyboard(direction, dt);
}

Game::Game()
    : window_{1024, 1024, "Minecraft++"}
    , camera_{static_cast<float>(window_.getWidth()) / static_cast<float>(window_.getHeight())}
    , guiContext_{window_.nativeHandle()}
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

void Game::render_()
{

}

void Game::run()
{
    glm::mat4 model = glm::mat4(1.0f);

    Shader shader("assets/shaders/ttest.vert", "assets/shaders/ttest.frag");
    shader.bind();

    Texture texture("assets/textures/dirt.png");
    texture.bind();

    double deltaTime = 0.0f;
    double lastFrame = 0.0f;

    Chunk chunk;

    for(size_t x{}; x < Chunk::Size; ++x) {
        for(size_t y{}; y < Chunk::Size; ++y) {
            for(size_t z{}; z < Chunk::Size; ++z) {
                chunk[x, y, z] = (y < 4) ? BlockType::Dirt : BlockType::Air;
            }
        }
    }
    std::cout << "built chunk\n";
    
    Mesh mesh = chunk.buildMesh();
    std::cout << "built mesh\n";
    ChunkRenderer renderer(mesh);
    std::cout << "created renderer\n";

    while(window_.isRunning()) {
        double currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        window_.pollEvents();
        processEvents_();

        processInputs_(deltaTime);

        ImVec4 clear_color = gui_.getClearColor();

        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // texture.Bind();
        // shader.Bind();
        glm::mat4 transform = camera_.getProjectionMatrix() * camera_.getViewMatrix() * model;
        shader.bind();
        shader.setMat4("transform", transform);
        renderer.draw(mesh.indices.size());

        // for(auto& position : blocks) {
        //     glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
        //     view = camera_.getViewMatrix();
        //     projection = camera_.getProjectionMatrix();
        //     shader.setMat4("transform", projection * view * model);
        //     glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
        // }
        
        guiContext_.StartFrame();
        ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
        gui_.OnUpdate();
        guiContext_.EndFrame();
        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
        
        window_.swapBuffers();
    }
}
