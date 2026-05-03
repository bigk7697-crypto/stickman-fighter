#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Engine {

// Types de caméra
enum class CameraType {
    FirstPerson,   // FPS (à l'intérieur du personnage)
    ThirdPerson,   // TPS (derrière le personnage)
    FreeFly        // Caméra libre (éditeur)
};

class Camera {
public:
    Camera(CameraType type = CameraType::ThirdPerson);
    
    // Configuration Third-Person
    void SetTarget(const glm::vec3& targetPosition);
    void SetDistance(float distance);
    void SetHeight(float height);
    
    // Contrôles
    void Rotate(float deltaYaw, float deltaPitch);  // Souris
    void Zoom(float delta);                          // Molette
    void Move(const glm::vec3& delta);               // Déplacement relatif
    void SetPosition(const glm::vec3& position);     // Position absolue
    
    // Getters matrices (pour les shaders)
    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix() const;
    
    // Getters utiles
    glm::vec3 GetPosition() const { return m_Position; }
    glm::vec3 GetForward() const { return m_Forward; }
    glm::vec3 GetRight() const { return m_Right; }
    glm::vec3 GetUp() const { return m_Up; }
    
    float GetYaw() const { return m_Yaw; }
    float GetPitch() const { return m_Pitch; }
    
    // Paramètres de projection
    void SetPerspective(float fovDegrees, float aspectRatio, float nearPlane, float farPlane);
    void SetAspectRatio(float aspectRatio);

    // Mode debug
    void PrintInfo() const;

private:
    CameraType m_Type;
    
    // Position et orientation
    glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 5.0f);
    glm::vec3 m_Forward = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 m_Right = glm::vec3(1.0f, 0.0f, 0.0f);
    
    // Angles d'Euler (en degrés)
    float m_Yaw = -90.0f;    // Rotation horizontale (autour de Y)
    float m_Pitch = 0.0f;    // Rotation verticale (autour de X)
    
    // Third-person spécifique
    glm::vec3 m_TargetPosition = glm::vec3(0.0f);
    float m_Distance = 5.0f;     // Distance derrière le joueur
    float m_Height = 2.0f;       // Hauteur au-dessus du joueur
    float m_MinDistance = 2.0f;  // Zoom minimum
    float m_MaxDistance = 15.0f; // Zoom maximum
    
    // Projection
    glm::mat4 m_Projection = glm::mat4(1.0f);
    float m_FOV = 60.0f;
    float m_AspectRatio = 4.0f / 3.0f;
    float m_NearPlane = 0.1f;
    float m_FarPlane = 100.0f;
    
    void UpdateVectors();  // Recalcule Forward/Right/Up depuis Yaw/Pitch
    void UpdateThirdPersonPosition();  // Positionne la caméra derrière le target
};

} // namespace Engine
