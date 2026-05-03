#pragma once
#include <functional>

namespace Game {

// Callbacks pour les événements de santé
using HealthChangedCallback = std::function<void(float currentHealth, float maxHealth)>;
using DeathCallback = std::function<void()>;

class HealthSystem {
public:
    HealthSystem(float maxHealth = 100.0f);
    
    // Propriétés
    float GetCurrentHealth() const { return m_CurrentHealth; }
    float GetMaxHealth() const { return m_MaxHealth; }
    float GetHealthPercent() const { return m_CurrentHealth / m_MaxHealth; }
    
    bool IsAlive() const { return m_CurrentHealth > 0.0f; }
    bool IsDead() const { return m_CurrentHealth <= 0.0f; }
    
    // Modification de la santé
    void TakeDamage(float damage);
    void Heal(float amount);
    void SetHealth(float health);
    void Reset();
    
    // Configuration
    void SetMaxHealth(float maxHealth, bool updateCurrent = true);
    void SetInvulnerable(bool invulnerable) { m_Invulnerable = invulnerable; }
    bool IsInvulnerable() const { return m_Invulnerable; }
    
    // Temps d'invincibilit après dégâts (i-frames)
    void SetInvincibilityTime(float seconds) { m_InvincibilityTime = seconds; }
    void Update(float deltaTime);
    bool IsInvincible() const { return m_InvincibilityTimer > 0.0f; }
    
    // Callbacks
    void SetOnHealthChanged(HealthChangedCallback callback) { m_OnHealthChanged = callback; }
    void SetOnDeath(DeathCallback callback) { m_OnDeath = callback; }
    void SetOnDamageTaken(std::function<void(float damage)> callback) { m_OnDamageTaken = callback; }

private:
    float m_MaxHealth;
    float m_CurrentHealth;
    bool m_Invulnerable = false;
    
    float m_InvincibilityTime = 0.0f;
    float m_InvincibilityTimer = 0.0f;
    
    // Callbacks
    HealthChangedCallback m_OnHealthChanged = nullptr;
    DeathCallback m_OnDeath = nullptr;
    std::function<void(float)> m_OnDamageTaken = nullptr;
};

} // namespace Game
