#include "Animator.h"
#include <cmath>
#include <iostream>

namespace Game {

Animator::Animator() = default;

void Animator::Play(AnimationType type, float duration) {
    m_CurrentAnimation = type;
    m_Duration = duration;
    m_Timer = 0.0f;
    m_IsPlaying = true;
    
    // Reset les modificateurs
    m_ScaleOffset = glm::vec3(0.0f);
    m_PositionOffset = glm::vec3(0.0f);
    m_RotationOffset = 0.0f;
    m_ColorModifier = glm::vec3(1.0f);
}

void Animator::PlayAttack(float duration) {
    Play(AnimationType::Attack, duration);
}

void Animator::PlayHit(float duration) {
    Play(AnimationType::Hit, duration);
}

void Animator::PlayDeath(float duration) {
    Play(AnimationType::Death, duration);
}

void Animator::Update(float deltaTime) {
    if (!m_IsPlaying) {
        // Animation idle par défaut
        m_Timer += deltaTime;
        UpdateIdle(m_Timer * 2.0f);  // Respiration lente
        return;
    }
    
    m_Timer += deltaTime;
    
    if (m_Timer >= m_Duration) {
        // Animation terminée
        if (m_CurrentAnimation == AnimationType::Death) {
            // La mort reste à l'état final
            m_Timer = m_Duration;
            float progress = 1.0f;
            UpdateDeath(progress);
        } else {
            Stop();
        }
        return;
    }
    
    float progress = m_Timer / m_Duration;
    
    switch (m_CurrentAnimation) {
        case AnimationType::Attack:
            UpdateAttack(progress);
            break;
        case AnimationType::Hit:
            UpdateHit(progress);
            break;
        case AnimationType::Death:
            UpdateDeath(progress);
            break;
        case AnimationType::Walk:
            UpdateWalk(progress);
            break;
        default:
            break;
    }
}

void Animator::UpdateAttack(float progress) {
    // Pulse: rapide expansion puis retour
    // 0-50%: expansion, 50-100%: retour
    float scale;
    if (progress < 0.5f) {
        float t = progress * 2.0f;  // 0 à 1
        scale = EaseOutQuad(t) * 0.3f;  // +30% scale max
    } else {
        float t = (progress - 0.5f) * 2.0f;  // 0 à 1
        scale = 0.3f - EaseInQuad(t) * 0.3f;  // Retour à 0
    }
    
    m_ScaleOffset = glm::vec3(scale);
    
    // Léger recul
    m_PositionOffset.z = -scale * 0.2f;
}

void Animator::UpdateHit(float progress) {
    // Flash rouge qui s'estompe
    if (progress < 0.3f) {
        // Rouge vif
        float t = progress / 0.3f;
        m_ColorModifier = glm::vec3(1.0f, 1.0f - t * 0.8f, 1.0f - t * 0.8f);
    } else {
        // Retour à la normale
        float t = (progress - 0.3f) / 0.7f;
        float r = 1.0f;
        float gb = 0.2f + t * 0.8f;  // 0.2 à 1.0
        m_ColorModifier = glm::vec3(r, gb, gb);
    }
    
    // Recul violent
    float recoil = sinf(progress * 3.14159f) * 0.5f;
    m_PositionOffset.z = recoil;
    
    // Scale pulse
    float scale = sinf(progress * 3.14159f) * 0.2f;
    m_ScaleOffset = glm::vec3(scale);
}

void Animator::UpdateDeath(float progress) {
    // Rotation + shrink
    m_RotationOffset = progress * 90.0f;  // Tourne de 90 degrés
    
    // Shrink vers le bas
    float scale = 1.0f - EaseInQuad(progress);
    m_ScaleOffset = glm::vec3(-scale * 0.7f);  -70% de taille
    
    // S'enfonce dans le sol
    m_PositionOffset.y = -progress * 0.5f;
    
    // Devient gris
    float gray = 1.0f - progress * 0.7f;  // 1.0 à 0.3
    m_ColorModifier = glm::vec3(gray, gray, gray);
}

void Animator::UpdateIdle(float progress) {
    // Respiration subtile
    // progress est déjà bouclé (time * 2)
    float t = fmodf(progress, 1.0f);
    float breathe = sinf(t * 3.14159f * 2.0f) * 0.02f;  // +/- 2%
    
    m_ScaleOffset = glm::vec3(breathe);
    m_PositionOffset.y = breathe * 0.1f;
}

void Animator::UpdateWalk(float progress) {
    // Oscillation gauche-droite
    float bob = sinf(progress * 3.14159f * 4.0f) * 0.05f;
    m_PositionOffset.y = bob;
    
    // Scale subtil
    float squash = sinf(progress * 3.14159f * 4.0f + 3.14159f/2.0f) * 0.05f;
    m_ScaleOffset = glm::vec3(-squash * 0.5f, squash, -squash * 0.5f);
}

float Animator::GetProgress() const {
    if (!m_IsPlaying || m_Duration <= 0.0f) return 0.0f;
    return std::min(m_Timer / m_Duration, 1.0f);
}

void Animator::Stop() {
    m_IsPlaying = false;
    m_CurrentAnimation = AnimationType::None;
    m_Timer = 0.0f;
    m_ScaleOffset = glm::vec3(0.0f);
    m_PositionOffset = glm::vec3(0.0f);
    m_RotationOffset = 0.0f;
    m_ColorModifier = glm::vec3(1.0f);
}

void Animator::Reset() {
    Stop();
}

} // namespace Game
