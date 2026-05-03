#pragma once
#include "../engine/AABB.h"
#include <glm/glm.hpp>
#include <vector>
#include <functional>

namespace Game {

class GameObject;

// Structure d'une attaque
struct Attack {
    glm::vec3 position;      // Centre de la hitbox
    glm::vec3 direction;   // Direction de l'attaque
    float range;            // Portée
    float width;            // Largeur de la hitbox
    float height;           // Hauteur de la hitbox
    float damage;           // Dégâts
    float cooldown;         // Temps de recharge (secondes)
    float duration;         // Durée de l'attaque (secondes)
    
    Attack() 
        : position(0.0f), direction(0.0f, 0.0f, 1.0f)
        , range(2.0f), width(1.5f), height(2.0f)
        , damage(10.0f), cooldown(0.5f), duration(0.2f) {}
};

// Callback quand une cible est touchée
using AttackHitCallback = std::function<void(GameObject* attacker, GameObject* target, float damage)>;

class CombatSystem {
public:
    CombatSystem();
    
    // Configurer l'attaque
    void SetAttackRange(float range) { m_Attack.range = range; }
    void SetAttackWidth(float width) { m_Attack.width = width; }
    void SetAttackHeight(float height) { m_Attack.height = height; }
    void SetAttackDamage(float damage) { m_Attack.damage = damage; }
    void SetAttackCooldown(float cooldown) { m_Attack.cooldown = cooldown; }
    void SetAttackDuration(float duration) { m_Attack.duration = duration; }
    float GetAttackDamage() const { return m_Attack.damage; }
    
    // Exécuter une attaque
    // Retourne true si l'attaque a été lancée
    bool Attack(GameObject* attacker, const glm::vec3& position, const glm::vec3& direction);
    
    // Mettre à jour le système (à appeler chaque frame)
    void Update(float deltaTime);
    
    // Vérifier si une attaque est en cours
    bool IsAttacking() const { return m_IsAttacking; }
    bool CanAttack() const { return m_CurrentCooldown <= 0.0f; }
    
    // Obtenir la progression de l'attaque (0.0 à 1.0)
    float GetAttackProgress() const;
    
    // Obtenir la hitbox actuelle de l'attaque (pour debug ou rendu)
    Engine::AABB GetCurrentHitbox() const;
    
    // Callbacks
    void SetOnHitCallback(AttackHitCallback callback) { m_OnHit = callback; }
    
    // Pour debug
    void PrintInfo() const;

private:
    Attack m_Attack;
    
    // État
    bool m_IsAttacking = false;
    float m_CurrentCooldown = 0.0f;
    float m_AttackTimer = 0.0f;
    
    // Attaque en cours
    GameObject* m_CurrentAttacker = nullptr;
    glm::vec3 m_AttackPosition;
    glm::vec3 m_AttackDirection;
    
    // Callbacks
    AttackHitCallback m_OnHit = nullptr;
    
    void EndAttack();
};

} // namespace Game
