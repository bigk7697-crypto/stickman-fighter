#include "CombatSystem.h"
#include "GameObject.h"
#include <iostream>
#include <cmath>

namespace Game {

CombatSystem::CombatSystem() = default;

bool CombatSystem::Attack(GameObject* attacker, const glm::vec3& position, const glm::vec3& direction) {
    // Vérifier si on peut attaquer (pas en cooldown)
    if (!CanAttack() || m_IsAttacking) {
        return false;
    }
    
    // Vérifier si le direction est valide
    if (glm::length(direction) < 0.001f) {
        std::cerr << "[Combat] Direction d'attaque invalide\n";
        return false;
    }
    
    // Lancer l'attaque
    m_IsAttacking = true;
    m_CurrentAttacker = attacker;
    m_AttackPosition = position;
    m_AttackDirection = glm::normalize(direction);
    m_AttackTimer = m_Attack.duration;
    
    std::cout << "[Combat] Attaque lancée! (durée: " << m_Attack.duration << "s)\n";
    
    return true;
}

void CombatSystem::Update(float deltaTime) {
    // Mettre à jour le cooldown
    if (m_CurrentCooldown > 0.0f) {
        m_CurrentCooldown -= deltaTime;
        if (m_CurrentCooldown < 0.0f) m_CurrentCooldown = 0.0f;
    }
    
    // Mettre à jour l'attaque en cours
    if (m_IsAttacking) {
        m_AttackTimer -= deltaTime;
        
        if (m_AttackTimer <= 0.0f) {
            EndAttack();
        }
    }
}

void CombatSystem::EndAttack() {
    if (!m_IsAttacking) return;
    
    m_IsAttacking = false;
    m_CurrentCooldown = m_Attack.cooldown;
    
    std::cout << "[Combat] Attaque terminée. Cooldown: " << m_Attack.cooldown << "s\n";
}

float CombatSystem::GetAttackProgress() const {
    if (!m_IsAttacking || m_Attack.duration <= 0.0f) {
        return 0.0f;
    }
    
    float progress = 1.0f - (m_AttackTimer / m_Attack.duration);
    return std::clamp(progress, 0.0f, 1.0f);
}

Engine::AABB CombatSystem::GetCurrentHitbox() const {
    if (!m_IsAttacking) {
        return Engine::AABB(glm::vec3(0.0f), glm::vec3(0.0f));
    }
    
    // Calculer le centre de la hitbox
    // Positionnée devant l'attaquant
    glm::vec3 hitboxCenter = m_AttackPosition + m_AttackDirection * (m_Attack.range * 0.5f);
    
    // Taille de la hitbox
    glm::vec3 hitboxSize(m_Attack.width, m_Attack.height, m_Attack.range);
    
    return Engine::AABB::FromCenterSize(hitboxCenter, hitboxSize);
}

void CombatSystem::PrintInfo() const {
    std::cout << "===== COMBAT SYSTEM =====\n";
    std::cout << "Attacking: " << (m_IsAttacking ? "OUI" : "NON") << "\n";
    std::cout << "Cooldown: " << m_CurrentCooldown << "s\n";
    std::cout << "Can Attack: " << (CanAttack() ? "OUI" : "NON") << "\n";
    std::cout << "Range: " << m_Attack.range << "\n";
    std::cout << "Damage: " << m_Attack.damage << "\n";
    std::cout << "=========================\n";
}

} // namespace Game
