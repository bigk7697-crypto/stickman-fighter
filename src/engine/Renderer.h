#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Engine {

class Renderer {
public:
    Renderer();
    ~Renderer();
    
    void Init();
    void Clear(const glm::vec3& color = glm::vec3(0.1f, 0.1f, 0.15f));
    void ClearDepth();
    
    // Configuration du rendu
    void SetDepthTest(bool enabled);
    void SetFaceCulling(bool enabled);
    void SetWireframeMode(bool enabled);
    void SetViewport(int x, int y, int width, int height);
    
    // Informations GPU
    static void PrintGPUInfo();
    
private:
    bool m_Initialized = false;
};

} // namespace Engine
