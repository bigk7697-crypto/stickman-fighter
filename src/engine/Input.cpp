#include "Input.h"
#include <GLFW/glfw3.h>
#include <iostream>

namespace Engine {

GLFWwindow* Input::s_Window = nullptr;

std::array<bool, 512> Input::s_Keys{};
std::array<bool, 512> Input::s_KeysPrevious{};

std::array<bool, 8> Input::s_MouseButtons{};
std::array<bool, 8> Input::s_MouseButtonsPrevious{};

double Input::s_MouseX = 0.0;
double Input::s_MouseY = 0.0;
double Input::s_LastMouseX = 0.0;
double Input::s_LastMouseY = 0.0;
double Input::s_MouseDeltaX = 0.0;
double Input::s_MouseDeltaY = 0.0;

double Input::s_ScrollDelta = 0.0;

bool Input::s_CursorVisible = true;
bool Input::s_FirstMouse = true;

void Input::Init(GLFWwindow* window) {
    s_Window = window;
    
    // Initialiser tous les états à false
    s_Keys.fill(false);
    s_KeysPrevious.fill(false);
    s_MouseButtons.fill(false);
    s_MouseButtonsPrevious.fill(false);
    
    // Obtenir la position initiale de la souris
    glfwGetCursorPos(window, &s_MouseX, &s_MouseY);
    s_LastMouseX = s_MouseX;
    s_LastMouseY = s_MouseY;
    
    std::cout << "[INFO] Input system initialisé\n";
}

void Input::Update() {
    // Sauvegarder les états précédents
    s_KeysPrevious = s_Keys;
    s_MouseButtonsPrevious = s_MouseButtons;
    
    // Mettre à jour le delta de souris
    s_MouseDeltaX = s_MouseX - s_LastMouseX;
    s_MouseDeltaY = s_MouseY - s_LastMouseY;
    
    s_LastMouseX = s_MouseX;
    s_LastMouseY = s_MouseY;
    
    // Réinitialiser le scroll (il est accumulé par les callbacks)
    // On garde la valeur jusqu'à ce qu'elle soit lue
}

// Clavier
bool Input::IsKeyPressed(int key) {
    if (key < 0 || key >= 512) return false;
    return s_Keys[key];
}

bool Input::IsKeyJustPressed(int key) {
    if (key < 0 || key >= 512) return false;
    return s_Keys[key] && !s_KeysPrevious[key];
}

bool Input::IsKeyReleased(int key) {
    if (key < 0 || key >= 512) return false;
    return !s_Keys[key] && s_KeysPrevious[key];
}

// Souris
bool Input::IsMouseButtonPressed(int button) {
    if (button < 0 || button >= 8) return false;
    return s_MouseButtons[button];
}

bool Input::IsMouseButtonJustPressed(int button) {
    if (button < 0 || button >= 8) return false;
    return s_MouseButtons[button] && !s_MouseButtonsPrevious[button];
}

bool Input::IsMouseButtonReleased(int button) {
    if (button < 0 || button >= 8) return false;
    return !s_MouseButtons[button] && s_MouseButtonsPrevious[button];
}

// Position souris
glm::vec2 Input::GetMousePosition() {
    return glm::vec2(static_cast<float>(s_MouseX), static_cast<float>(s_MouseY));
}

glm::vec2 Input::GetMouseDelta() {
    // Si la souris est cachée (mode caméra), on retourne le delta
    // Sinon on retourne 0 pour éviter les mouvements accidentels
    if (!s_CursorVisible) {
        return glm::vec2(static_cast<float>(s_MouseDeltaX), static_cast<float>(s_MouseDeltaY));
    }
    return glm::vec2(0.0f, 0.0f);
}

void Input::SetMousePosition(float x, float y) {
    if (s_Window) {
        glfwSetCursorPos(s_Window, x, y);
        s_MouseX = x;
        s_MouseY = y;
        s_LastMouseX = x;
        s_LastMouseY = y;
    }
}

// Molette
float Input::GetMouseScrollDelta() {
    return static_cast<float>(s_ScrollDelta);
}

void Input::ResetScrollDelta() {
    s_ScrollDelta = 0.0;
}

// Curseur
void Input::SetCursorVisible(bool visible) {
    s_CursorVisible = visible;
    if (s_Window) {
        glfwSetInputMode(s_Window, GLFW_CURSOR, 
            visible ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
        
        if (!visible) {
            // Réinitialiser pour éviter le saut
            s_FirstMouse = true;
        }
    }
}

bool Input::IsCursorVisible() {
    return s_CursorVisible;
}

// Callbacks
void Input::KeyCallback(int key, int action) {
    if (key >= 0 && key < 512) {
        if (action == GLFW_PRESS) {
            s_Keys[key] = true;
        } else if (action == GLFW_RELEASE) {
            s_Keys[key] = false;
        }
        // GLFW_REPEAT est ignoré (la touche reste pressed)
    }
}

void Input::MouseButtonCallback(int button, int action) {
    if (button >= 0 && button < 8) {
        if (action == GLFW_PRESS) {
            s_MouseButtons[button] = true;
        } else if (action == GLFW_RELEASE) {
            s_MouseButtons[button] = false;
        }
    }
}

void Input::CursorPosCallback(double xpos, double ypos) {
    s_MouseX = xpos;
    s_MouseY = ypos;
    
    if (s_FirstMouse) {
        s_LastMouseX = xpos;
        s_LastMouseY = ypos;
        s_FirstMouse = false;
    }
}

void Input::ScrollCallback(double xoffset, double yoffset) {
    s_ScrollDelta += yoffset;  // Accumuler (peut recevoir plusieurs événements par frame)
}

} // namespace Engine
