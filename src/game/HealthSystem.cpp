#include "HealthSystem.h"
#include <iostream>
#include <algorithm>

namespace Game {

HealthSystem::HealthSystem(float maxHealth)
    : m_MaxHealth(maxHealth), m_CurrentHealth(maxHealth) {
}

void HealthSystem::TakeDamage(float damage) {
    if (damage <= 0.0f) return;
    
    if (m_Invulnerable || IsInvincible()) {
        std::cout << "[Health] Dégâts ignorés (invincible)\n";
        return;
    }
    
    m_CurrentHealth -= damage;
    if (m_CurrentHealth < 0.0f) m_CurrentHealth = 0.0f;
    
    std::cout << "[Health] -" << damage << " PV! (" << m_CurrentHealth << "/" << m_MaxHealth << ")\n";
    
    // Déclencher i-frames
    if (m_InvincibilityTime > 0.0f) {
        m_InvincibilityTimer = m_InvincibilityTime;
    }
    
    // Callbacks
    if (m_OnDamageTaken) {
        m_OnDamageTaken(damage);
    }
    
    if (m_OnHealthChanged) {
        m_OnHealthChanged(m_CurrentHealth, m_MaxHealth);
    }
    
    // Mort ?
    if (m_CurrentHealth <= 0.0f && m_OnDeath) {
        std::cout << "[Health] MORT!\n";
        m_OnDeath();
    }
}

void HealthSystem::Heal(float amount) {
    if (amount <= 0.0f || m_CurrentHealth >= m_MaxHealth) return;
    
    m_CurrentHealth += amount;
    if (m_CurrentHealth > m_MaxHealth) m_CurrentHealth = m_MaxHealth;
    
    std::cout << "[Health] +" << amount << " PV! (" << m_CurrentHealth << "/" << m_MaxHealth << ")\n";
    
    if (m_OnHealthChanged) {
        m_OnHealthChanged(m_CurrentHealth, m_MaxHealth);
    }
}

void HealthSystem::SetHealth(float health) {
    m_CurrentHealth = std::clamp(health, 0.0f, m_MaxHealth);
    
    if (m_OnHealthChanged) {
        m_OnHealthChanged(m_CurrentHealth, m_MaxHealth);
    }
    
    if (m_CurrentHealth <= 0.0f && m_OnDeath) {
        m_OnDeath();
    }
}

void HealthSystem::Reset() {
    m_CurrentHealth = m_MaxHealth;
    m_InvincibilityTimer = 0.0f;
    
    if (m_OnHealthChanged) {
        m_OnHealthChanged(m_CurrentHealth, m_MaxHealth);
    }
}

void HealthSystem::SetMaxHealth(float maxHealth, bool updateCurrent) {
    m_MaxHealth = maxHealth;
    if (updateCurrent) {
        m_CurrentHealth = maxHealth;
    } else {
        m_CurrentHealth = std::min(m_CurrentHealth, maxHealth);
    }
}

void HealthSystem::Update(float deltaTime) {
    if (m_InvincibilityTimer > 0.0f) {
        m_InvincibilityTimer -= deltaTime;
        if (m_InvincibilityTimer < 0.0f) {
            m_InvincibilityTimer = 0.0f;
            std::cout << "[Health] Invincibilité terminée\n";
        }
    }
}

} // namespace Game
