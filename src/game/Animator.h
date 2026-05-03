#pragma once
#include <glm/glm.hpp>
#include <functional>
#include <string>

namespace Game {

// Types d'animation
enum class AnimationType {
    None,
    Attack,      // Pulse de scale
    Hit,         // Flash rouge + recul
    Death,       // Rotation + shrink
    Idle,        // Respiration légère
    Walk         // Oscillation
};

// Classe pour animer les GameObjects
class Animator {
public:
    Animator();
    
    // Démarrer une animation
    void Play(AnimationType type, float duration);
    void PlayAttack(float duration = 0.2f);
    void PlayHit(float duration = 0.3f);
    void PlayDeath(float duration = 1.0f);
    
    // Mettre à jour l'animation
    void Update(float deltaTime);
    
    // Obtenir les modifications actuelles
    glm::vec3 GetScaleOffset() const { return m_ScaleOffset; }
    glm::vec3 GetPositionOffset() const { return m_PositionOffset; }
    glm::vec3 GetColorModifier() const { return m_ColorModifier; }
    float GetRotationOffset() const { return m_RotationOffset; }
    
    // État
    bool IsPlaying() const { return m_IsPlaying; }
    AnimationType GetCurrentAnimation() const { return m_CurrentAnimation; }
    float GetProgress() const;  // 0.0 à 1.0
    
    // Arrêter l'animation
    void Stop();
    
    // Reset
    void Reset();
    
private:
    AnimationType m_CurrentAnimation = AnimationType::None;
    bool m_IsPlaying = false;
    
    float m_Timer = 0.0f;
    float m_Duration = 0.0f;
    
    // Modificateurs de transform
    glm::vec3 m_ScaleOffset = glm::vec3(0.0f);
    glm::vec3 m_PositionOffset = glm::vec3(0.0f);
    float m_RotationOffset = 0.0f;
    
    // Modificateur de couleur (multiplicateur)
    glm::vec3 m_ColorModifier = glm::vec3(1.0f);
    
    // Mise à jour spécifique par type
    void UpdateAttack(float progress);
    void UpdateHit(float progress);
    void UpdateDeath(float progress);
    void UpdateIdle(float progress);
    void UpdateWalk(float progress);
    
    // Interpolation utilitaire
    float EaseOutQuad(float t) const { return 1.0f - (1.0f - t) * (1.0f - t); }
    float EaseInQuad(float t) const { return t * t; }
    float EaseInOutQuad(float t) const {
        return t < 0.5f ? 2.0f * t * t : 1.0f - powf(-2.0f * t + 2.0f, 2.0f) / 2.0f;
    }
    float ElasticOut(float t) const {
        const float c4 = (2.0f * 3.14159265359f) / 3.0f;
        return t == 0.0f ? 0.0f : t == 1.0f ? 1.0f : powf(2.0f, -10.0f * t) * sinf((t * 10.0f - 0.75f) * c4) + 1.0f;
    }
};

} // namespace Game
