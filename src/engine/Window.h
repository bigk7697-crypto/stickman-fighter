#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <functional>

namespace Engine {

class Window {
public:
    Window(int width, int height, const std::string& title);
    ~Window();

    bool ShouldClose() const;
    void SwapBuffers();
    void PollEvents();
    
    // Callbacks
    using ResizeCallback = std::function<void(int, int)>;
    using KeyCallback = std::function<void(int, int, int, int)>;
    
    void SetResizeCallback(ResizeCallback callback);
    void SetKeyCallback(KeyCallback callback);

    // Getters
    int GetWidth() const { return m_Width; }
    int GetHeight() const { return m_Height; }
    GLFWwindow* GetNativeWindow() const { return m_Window; }

    // État des touches
    bool IsKeyPressed(int key) const;

private:
    GLFWwindow* m_Window = nullptr;
    int m_Width;
    int m_Height;
    
    ResizeCallback m_ResizeCallback;
    KeyCallback m_KeyCallback;
    
    static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void KeyCallbackStatic(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void MouseButtonCallbackStatic(GLFWwindow* window, int button, int action, int mods);
    static void CursorPosCallbackStatic(GLFWwindow* window, double xpos, double ypos);
    static void ScrollCallbackStatic(GLFWwindow* window, double xoffset, double yoffset);
    
    void Init();
    void Shutdown();
};

} // namespace Engine
