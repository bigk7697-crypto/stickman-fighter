#include "Camera.h"
#include <iostream>
#include <cmath>

namespace Engine {

Camera::Camera(CameraType type) 
    : m_Type(type) {
    UpdateVectors();
    SetPerspective(m_FOV, m_AspectRatio, m_NearPlane, m_FarPlane);
}

void Camera::SetPerspective(float fovDegrees, float aspectRatio, float nearPlane, float farPlane) {
    m_FOV = fovDegrees;
    m_AspectRatio = aspectRatio;
    m_NearPlane = nearPlane;
    m_FarPlane = farPlane;
    m_Projection = glm::perspective(glm::radians(fovDegrees), aspectRatio, nearPlane, farPlane);
}

void Camera::SetAspectRatio(float aspectRatio) {
    m_AspectRatio = aspectRatio;
    m_Projection = glm::perspective(glm::radians(m_FOV), aspectRatio, m_NearPlane, m_FarPlane);
}

void Camera::UpdateVectors() {
    // Convertir angles d'Euler en vecteur direction
    float yawRad = glm::radians(m_Yaw);
    float pitchRad = glm::radians(m_Pitch);
    
    // Forward vector
    m_Forward.x = cos(pitchRad) * cos(yawRad);
    m_Forward.y = sin(pitchRad);
    m_Forward.z = cos(pitchRad) * sin(yawRad);
    m_Forward = glm::normalize(m_Forward);
    
    // Right et Up (repère orthonormé)
    m_Right = glm::normalize(glm::cross(m_Forward, glm::vec3(0.0f, 1.0f, 0.0f)));
    m_Up = glm::normalize(glm::cross(m_Right, m_Forward));
}

void Camera::Rotate(float deltaYaw, float deltaPitch) {
    m_Yaw += deltaYaw;
    m_Pitch += deltaPitch;
    
    // Limiter le pitch pour éviter le flip (gimbal lock)
    if (m_Pitch > 89.0f) m_Pitch = 89.0f;
    if (m_Pitch < -89.0f) m_Pitch = -89.0f;
    
    UpdateVectors();
    
    if (m_Type == CameraType::ThirdPerson) {
        UpdateThirdPersonPosition();
    }
}

void Camera::Zoom(float delta) {
    m_Distance -= delta;
    
    // Clamper la distance
    if (m_Distance < m_MinDistance) m_Distance = m_MinDistance;
    if (m_Distance > m_MaxDistance) m_Distance = m_MaxDistance;
    
    if (m_Type == CameraType::ThirdPerson) {
        UpdateThirdPersonPosition();
    }
}

void Camera::SetTarget(const glm::vec3& targetPosition) {
    m_TargetPosition = targetPosition;
    
    if (m_Type == CameraType::ThirdPerson) {
        UpdateThirdPersonPosition();
    }
}

void Camera::SetDistance(float distance) {
    m_Distance = distance;
    if (m_Distance < m_MinDistance) m_Distance = m_MinDistance;
    if (m_Distance > m_MaxDistance) m_Distance = m_MaxDistance;
    
    if (m_Type == CameraType::ThirdPerson) {
        UpdateThirdPersonPosition();
    }
}

void Camera::SetHeight(float height) {
    m_Height = height;
    
    if (m_Type == CameraType::ThirdPerson) {
        UpdateThirdPersonPosition();
    }
}

void Camera::UpdateThirdPersonPosition() {
    // Calculer la position de la caméra derrière le target
    // On inverse le forward pour être DERrière le personnage
    float yawRad = glm::radians(m_Yaw);
    float pitchRad = glm::radians(m_Pitch);
    
    // Direction de la caméra (opposée au regard du joueur)
    glm::vec3 offset;
    offset.x = -cos(pitchRad) * cos(yawRad) * m_Distance;
    offset.y = sin(pitchRad) * m_Distance + m_Height;
    offset.z = -cos(pitchRad) * sin(yawRad) * m_Distance;
    
    m_Position = m_TargetPosition + offset;
}

void Camera::Move(const glm::vec3& delta) {
    // Déplacement relatif (pour free-fly ou ajustement)
    m_Position += m_Forward * delta.z;
    m_Position += m_Right * delta.x;
    m_Position += m_Up * delta.y;
}

void Camera::SetPosition(const glm::vec3& position) {
    m_Position = position;
}

glm::mat4 Camera::GetViewMatrix() const {
    if (m_Type == CameraType::ThirdPerson) {
        // En third-person, on regarde le target
        return glm::lookAt(m_Position, m_TargetPosition, m_Up);
    } else {
        // En first-person, on regarde devant
        return glm::lookAt(m_Position, m_Position + m_Forward, m_Up);
    }
}

glm::mat4 Camera::GetProjectionMatrix() const {
    return m_Projection;
}

void Camera::PrintInfo() const {
    std::cout << "===== CAMERA INFO =====\n";
    std::cout << "Type: " << (m_Type == CameraType::ThirdPerson ? "Third-Person" : 
                               m_Type == CameraType::FirstPerson ? "First-Person" : "Free-Fly") << "\n";
    std::cout << "Position: [" << m_Position.x << ", " << m_Position.y << ", " << m_Position.z << "]\n";
    std::cout << "Forward:  [" << m_Forward.x << ", " << m_Forward.y << ", " << m_Forward.z << "]\n";
    std::cout << "Yaw: " << m_Yaw << "°, Pitch: " << m_Pitch << "°\n";
    std::cout << "Distance: " << m_Distance << ", Height: " << m_Height << "\n";
    std::cout << "=======================\n";
}

} // namespace Engine
