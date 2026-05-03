#include "Renderer.h"
#include <iostream>

namespace Engine {

Renderer::Renderer() = default;

Renderer::~Renderer() = default;

void Renderer::Init() {
    // Configuration OpenGL par défaut
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    
    // Blend pour transparence (futur)
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    m_Initialized = true;
    std::cout << "[INFO] Renderer initialisé\n";
}

void Renderer::Clear(const glm::vec3& color) {
    glClearColor(color.r, color.g, color.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::ClearDepth() {
    glClear(GL_DEPTH_BUFFER_BIT);
}

void Renderer::SetDepthTest(bool enabled) {
    if (enabled) glEnable(GL_DEPTH_TEST);
    else glDisable(GL_DEPTH_TEST);
}

void Renderer::SetFaceCulling(bool enabled) {
    if (enabled) glEnable(GL_CULL_FACE);
    else glDisable(GL_CULL_FACE);
}

void Renderer::SetWireframeMode(bool enabled) {
    glPolygonMode(GL_FRONT_AND_BACK, enabled ? GL_LINE : GL_FILL);
}

void Renderer::SetViewport(int x, int y, int width, int height) {
    glViewport(x, y, width, height);
}

void Renderer::PrintGPUInfo() {
    std::cout << "===== GPU INFO =====\n";
    std::cout << "Vendor:   " << glGetString(GL_VENDOR) << "\n";
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << "\n";
    std::cout << "Version:  " << glGetString(GL_VERSION) << "\n";
    std::cout << "GLSL:     " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";
    std::cout << "====================\n";
}

} // namespace Engine
