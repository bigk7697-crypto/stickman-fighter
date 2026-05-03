#pragma once
#include <glm/glm.hpp>
#include <array>

// Forward declaration
struct GLFWwindow;

namespace Engine {

class Input {
public:
    static void Init(GLFWwindow* window);
    static void Update();  // À appeler chaque frame
    
    // Clavier
    static bool IsKeyPressed(int key);
    static bool IsKeyJustPressed(int key);   // Une seule fois par appui
    static bool IsKeyReleased(int key);
    
    // Souris
    static bool IsMouseButtonPressed(int button);
    static bool IsMouseButtonJustPressed(int button);
    static bool IsMouseButtonReleased(int button);
    
    // Position souris
    static glm::vec2 GetMousePosition();
    static glm::vec2 GetMouseDelta();        // Déplacement depuis la dernière frame
    static void SetMousePosition(float x, float y);
    
    // Molette
    static float GetMouseScrollDelta();
    static void ResetScrollDelta();
    
    // Capture/Release souris
    static void SetCursorVisible(bool visible);
    static bool IsCursorVisible();
    
    // Callbacks internes (appelés par Window)
    static void KeyCallback(int key, int action);
    static void MouseButtonCallback(int button, int action);
    static void CursorPosCallback(double xpos, double ypos);
    static void ScrollCallback(double xoffset, double yoffset);

private:
    static GLFWwindow* s_Window;
    
    // États clavier (GLFW a des codes de 0 à 348)
    static std::array<bool, 512> s_Keys;
    static std::array<bool, 512> s_KeysPrevious;
    
    // États souris (0 = gauche, 1 = droit, 2 = milieu)
    static std::array<bool, 8> s_MouseButtons;
    static std::array<bool, 8> s_MouseButtonsPrevious;
    
    // Position souris
    static double s_MouseX;
    static double s_MouseY;
    static double s_LastMouseX;
    static double s_LastMouseY;
    static double s_MouseDeltaX;
    static double s_MouseDeltaY;
    
    // Scroll
    static double s_ScrollDelta;
    
    static bool s_CursorVisible;
    static bool s_FirstMouse;  // Pour éviter le saut au démarrage
};

// Codes de touches utiles (simplifiés)
namespace Key {
    constexpr int Space = 32;
    constexpr int Escape = 256;
    constexpr int Enter = 257;
    constexpr int Tab = 258;
    constexpr int Backspace = 259;
    constexpr int Insert = 260;
    constexpr int Delete = 261;
    constexpr int Right = 262;
    constexpr int Left = 263;
    constexpr int Down = 264;
    constexpr int Up = 265;
    constexpr int PageUp = 266;
    constexpr int PageDown = 267;
    constexpr int Home = 268;
    constexpr int End = 269;
    constexpr int CapsLock = 280;
    constexpr int ScrollLock = 281;
    constexpr int NumLock = 282;
    constexpr int PrintScreen = 283;
    constexpr int Pause = 284;
    constexpr int F1 = 290;
    constexpr int F2 = 291;
    constexpr int F3 = 292;
    constexpr int F4 = 293;
    constexpr int F5 = 294;
    constexpr int F6 = 295;
    constexpr int F7 = 296;
    constexpr int F8 = 297;
    constexpr int F9 = 298;
    constexpr int F10 = 299;
    constexpr int F11 = 300;
    constexpr int F12 = 301;
    constexpr int LeftShift = 340;
    constexpr int LeftControl = 341;
    constexpr int LeftAlt = 342;
    constexpr int LeftSuper = 343;  // Windows key
    constexpr int RightShift = 344;
    constexpr int RightControl = 345;
    constexpr int RightAlt = 346;
    constexpr int RightSuper = 347;
    constexpr int Menu = 348;
    
    // Lettres
    constexpr int A = 65;
    constexpr int B = 66;
    constexpr int C = 67;
    constexpr int D = 68;
    constexpr int E = 69;
    constexpr int F = 70;
    constexpr int G = 71;
    constexpr int H = 72;
    constexpr int I = 73;
    constexpr int J = 74;
    constexpr int K = 75;
    constexpr int L = 76;
    constexpr int M = 77;
    constexpr int N = 78;
    constexpr int O = 79;
    constexpr int P = 80;
    constexpr int Q = 81;
    constexpr int R = 82;
    constexpr int S = 83;
    constexpr int T = 84;
    constexpr int U = 85;
    constexpr int V = 86;
    constexpr int W = 87;
    constexpr int X = 88;
    constexpr int Y = 89;
    constexpr int Z = 90;
}

namespace Mouse {
    constexpr int Left = 0;
    constexpr int Right = 1;
    constexpr int Middle = 2;
}

} // namespace Engine
