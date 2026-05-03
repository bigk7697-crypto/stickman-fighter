#include "Window.h"
#include "Input.h"
#include <iostream>

namespace Engine {

Window::Window(int width, int height, const std::string& title)
    : m_Width(width), m_Height(height) {
    
    // Initialisation GLFW
    if (!glfwInit()) {
        std::cerr << "[ERREUR] Échec initialisation GLFW\n";
        return;
    }
    
    // Configuration OpenGL 3.3 Core Profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4); // Anti-aliasing
    
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
    
    // Création fenêtre
    m_Window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!m_Window) {
        std::cerr << "[ERREUR] Échec création fenêtre GLFW\n";
        glfwTerminate();
        return;
    }
    
    // Rendre le contexte courant
    glfwMakeContextCurrent(m_Window);
    
    // Charger les fonctions OpenGL via GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "[ERREUR] Échec initialisation GLAD\n";
        return;
    }
    
    // Configuration viewport
    glViewport(0, 0, width, height);
    
    // Activer V-Sync (limiter à 60 FPS)
    glfwSwapInterval(1);
    
    // Enregistrer les callbacks
    glfwSetWindowUserPointer(m_Window, this);
    glfwSetFramebufferSizeCallback(m_Window, FramebufferSizeCallback);
    glfwSetKeyCallback(m_Window, KeyCallbackStatic);
    glfwSetMouseButtonCallback(m_Window, MouseButtonCallbackStatic);
    glfwSetCursorPosCallback(m_Window, CursorPosCallbackStatic);
    glfwSetScrollCallback(m_Window, ScrollCallbackStatic);
    
    // Initialiser le système Input
    Input::Init(m_Window);
    
    std::cout << "[INFO] Fenêtre créée: " << width << "x" << height << "\n";
    std::cout << "[INFO] OpenGL " << glGetString(GL_VERSION) << "\n";
}

Window::~Window() {
    Shutdown();
}

void Window::Shutdown() {
    if (m_Window) {
        glfwDestroyWindow(m_Window);
        m_Window = nullptr;
    }
    glfwTerminate();
    std::cout << "[INFO] Fenêtre détruite\n";
}

bool Window::ShouldClose() const {
    return glfwWindowShouldClose(m_Window);
}

void Window::SwapBuffers() {
    glfwSwapBuffers(m_Window);
}

void Window::PollEvents() {
    glfwPollEvents();
}

bool Window::IsKeyPressed(int key) const {
    return glfwGetKey(m_Window, key) == GLFW_PRESS;
}

void Window::SetResizeCallback(ResizeCallback callback) {
    m_ResizeCallback = callback;
}

void Window::SetKeyCallback(KeyCallback callback) {
    m_KeyCallback = callback;
}

// Callback statique GLFW
void Window::FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
    Window* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (self) {
        self->m_Width = width;
        self->m_Height = height;
        glViewport(0, 0, width, height);
        if (self->m_ResizeCallback) {
            self->m_ResizeCallback(width, height);
        }
    }
}

void Window::KeyCallbackStatic(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // Transmettre à Input d'abord
    Input::KeyCallback(key, action);
    
    // Puis au callback utilisateur si défini
    Window* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (self && self->m_KeyCallback) {
        self->m_KeyCallback(key, scancode, action, mods);
    }
}

void Window::MouseButtonCallbackStatic(GLFWwindow* window, int button, int action, int mods) {
    Input::MouseButtonCallback(button, action);
}

void Window::CursorPosCallbackStatic(GLFWwindow* window, double xpos, double ypos) {
    Input::CursorPosCallback(xpos, ypos);
}

void Window::ScrollCallbackStatic(GLFWwindow* window, double xoffset, double yoffset) {
    Input::ScrollCallback(xoffset, yoffset);
}

} // namespace Engine
