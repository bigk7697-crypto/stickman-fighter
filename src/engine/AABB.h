#pragma once
#include <glm/glm.hpp>
#include <algorithm>

namespace Engine {

// Axis-Aligned Bounding Box
// Une boîte dont les faces sont alignées avec les axes X, Y, Z
struct AABB {
    glm::vec3 min;  // Coin inférieur gauche arrière
    glm::vec3 max;  // Coin supérieur droit avant
    
    AABB() : min(0.0f), max(0.0f) {}
    AABB(const glm::vec3& minPoint, const glm::vec3& maxPoint) 
        : min(minPoint), max(maxPoint) {}
    
    // Créer une AABB depuis un centre et des dimensions
    static AABB FromCenterSize(const glm::vec3& center, const glm::vec3& size) {
        glm::vec3 halfSize = size * 0.5f;
        return AABB(center - halfSize, center + halfSize);
    }
    
    // Propriétés
    glm::vec3 GetCenter() const { return (min + max) * 0.5f; }
    glm::vec3 GetSize() const { return max - min; }
    glm::vec3 GetHalfSize() const { return (max - min) * 0.5f; }
    
    float GetWidth() const { return max.x - min.x; }
    float GetHeight() const { return max.y - min.y; }
    float GetDepth() const { return max.z - min.z; }
    
    float GetVolume() const {
        glm::vec3 size = GetSize();
        return size.x * size.y * size.z;
    }
    
    // Déplacer la boîte
    void Translate(const glm::vec3& offset) {
        min += offset;
        max += offset;
    }
    
    void SetCenter(const glm::vec3& center) {
        glm::vec3 halfSize = GetHalfSize();
        min = center - halfSize;
        max = center + halfSize;
    }
    
    // Vérifier si un point est à l'intérieur
    bool Contains(const glm::vec3& point) const {
        return point.x >= min.x && point.x <= max.x &&
               point.y >= min.y && point.y <= max.y &&
               point.z >= min.z && point.z <= max.z;
    }
    
    // Vérifier si cette AABB contient une autre AABB entièrement
    bool Contains(const AABB& other) const {
        return Contains(other.min) && Contains(other.max);
    }
    
    // TEST DE COLLISION PRINCIPAL
    // Vérifier si deux AABB se chevauchent
    bool Intersects(const AABB& other) const {
        return (min.x <= other.max.x && max.x >= other.min.x) &&
               (min.y <= other.max.y && max.y >= other.min.y) &&
               (min.z <= other.max.z && max.z >= other.min.z);
    }
    
    // Calculer le vecteur de pénétration (pour repousser les objets)
    // Retourne le vecteur minimal pour séparer les deux boîtes
    glm::vec3 GetPenetrationVector(const AABB& other) const {
        if (!Intersects(other)) {
            return glm::vec3(0.0f);
        }
        
        // Calculer les chevauchements sur chaque axe
        float overlapX = std::min(max.x, other.max.x) - std::max(min.x, other.min.x);
        float overlapY = std::min(max.y, other.max.y) - std::max(min.y, other.min.y);
        float overlapZ = std::min(max.z, other.max.z) - std::max(min.z, other.min.z);
        
        // Trouver l'axe avec le moins de chevauchement (pénétration la plus faible)
        glm::vec3 penetration(0.0f);
        
        float minOverlap = overlapX;
        int axis = 0;  // X
        
        if (overlapY < minOverlap) {
            minOverlap = overlapY;
            axis = 1;  // Y
        }
        
        if (overlapZ < minOverlap) {
            minOverlap = overlapZ;
            axis = 2;  // Z
        }
        
        // Déterminer la direction selon l'axe
        glm::vec3 centerA = GetCenter();
        glm::vec3 centerB = other.GetCenter();
        
        switch (axis) {
            case 0:  // X
                penetration.x = (centerA.x < centerB.x) ? -overlapX : overlapX;
                break;
            case 1:  // Y
                penetration.y = (centerA.y < centerB.y) ? -overlapY : overlapY;
                break;
            case 2:  // Z
                penetration.z = (centerA.z < centerB.z) ? -overlapZ : overlapZ;
                break;
        }
        
        return penetration;
    }
    
    // Calculer l'aire/volume de chevauchement
    float GetIntersectionVolume(const AABB& other) const {
        if (!Intersects(other)) return 0.0f;
        
        float xOverlap = std::min(max.x, other.max.x) - std::max(min.x, other.min.x);
        float yOverlap = std::min(max.y, other.max.y) - std::max(min.y, other.min.y);
        float zOverlap = std::min(max.z, other.max.z) - std::max(min.z, other.min.z);
        
        return xOverlap * yOverlap * zOverlap;
    }
    
    // Étendre cette AABB pour inclure un point ou une autre AABB
    void Expand(const glm::vec3& point) {
        min = glm::min(min, point);
        max = glm::max(max, point);
    }
    
    void Expand(const AABB& other) {
        min = glm::min(min, other.min);
        max = glm::max(max, other.max);
    }
    
    // Créer une AABB légèrement plus grande (marge de sécurité)
    AABB Inflate(float amount) const {
        glm::vec3 offset(amount);
        return AABB(min - offset, max + offset);
    }
};

} // namespace Engine
