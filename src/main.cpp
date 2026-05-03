#include "engine/Window.h"
#include "engine/Renderer.h"
#include "engine/Shader.h"
#include "engine/Mesh.h"
#include "engine/Camera.h"
#include "engine/Input.h"
#include "game/GameObject.h"
#include "game/CombatSystem.h"
#include "game/HealthSystem.h"
#include <iostream>
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

// ÉTAPE 6: Animations et effets visuels

int main() {
    std::cout << "=== Stickman Fighter - Etape 6 ===\n";
    std::cout << "Animations et effets visuels...\n\n";
    
    // 1. Créer la fenêtre
    Engine::Window window(800, 600, "Stickman Fighter - Etape 6 (Animation)");
    
    // 2. Initialiser le renderer
    Engine::Renderer renderer;
    renderer.Init();
    Engine::Renderer::PrintGPUInfo();
    
    // 3. Créer les shaders
    Engine::Shader shader;
    
    const std::string vertexShader = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec3 aColor;
        out vec3 vColor;
        uniform mat4 u_Model;
        uniform mat4 u_View;
        uniform mat4 u_Projection;
        void main() {
            vColor = aColor;
            gl_Position = u_Projection * u_View * u_Model * vec4(aPos, 1.0);
        }
    )";
    
    const std::string fragmentShader = R"(
        #version 330 core
        in vec3 vColor;
        out vec4 FragColor;
        void main() {
            FragColor = vec4(vColor, 1.0);
        }
    )";
    
    if (!shader.LoadFromSource(vertexShader, fragmentShader)) {
        std::cerr << "[ERREUR] Impossible de charger les shaders\n";
        return -1;
    }
    
    // 4. Créer les meshes
    Engine::Mesh cubeMesh = Engine::Mesh::CreateCube(1.0f);
    
    // 5. Créer le joueur
    Game::GameObject player("Joueur", Game::ObjectType::Player);
    player.SetMesh(cubeMesh);
    player.SetPosition(glm::vec3(-3.0f, 0.5f, -3.0f));  // Position de départ
    player.SetScale(glm::vec3(1.0f));
    player.SetCollisionBox(glm::vec3(1.0f));
    
    // Santé du joueur
    Game::HealthSystem playerHealth(100.0f);
    playerHealth.SetOnHealthChanged([&player](float current, float max) {
        std::cout << "[Joueur] PV: " << current << "/" << max << "\n";
    });
    playerHealth.SetOnDamageTaken([&player](float damage) {
        // Animation de dégâts
        player.GetAnimator().PlayHit();
    });
    playerHealth.SetOnDeath([&player]() {
        std::cout << "\n*** JOUEUR MORT! ***\n\n";
        player.GetAnimator().PlayDeath();
    });
    
    // Système de combat du joueur
    Game::CombatSystem playerCombat;
    playerCombat.SetAttackDamage(25.0f);
    playerCombat.SetAttackRange(2.5f);
    playerCombat.SetAttackWidth(1.5f);
    playerCombat.SetAttackCooldown(0.4f);
    playerCombat.SetAttackDuration(0.2f);
    
    player.PrintInfo();
    
    // 6. Créer des obstacles (murs)
    std::vector<Game::GameObject> obstacles;
    
    // Mur Nord
    Game::GameObject wall1("Mur Nord", Game::ObjectType::Obstacle);
    wall1.SetMesh(cubeMesh);
    wall1.SetPosition(glm::vec3(0.0f, 1.0f, -10.0f));
    wall1.SetScale(glm::vec3(20.0f, 2.0f, 1.0f));  // Long mur horizontal
    wall1.SetCollisionBox(glm::vec3(20.0f, 2.0f, 1.0f));
    obstacles.push_back(wall1);
    
    // Mur Sud
    Game::GameObject wall2("Mur Sud", Game::ObjectType::Obstacle);
    wall2.SetMesh(cubeMesh);
    wall2.SetPosition(glm::vec3(0.0f, 1.0f, 10.0f));
    wall2.SetScale(glm::vec3(20.0f, 2.0f, 1.0f));
    wall2.SetCollisionBox(glm::vec3(20.0f, 2.0f, 1.0f));
    obstacles.push_back(wall2);
    
    // Mur Est
    Game::GameObject wall3("Mur Est", Game::ObjectType::Obstacle);
    wall3.SetMesh(cubeMesh);
    wall3.SetPosition(glm::vec3(10.0f, 1.0f, 0.0f));
    wall3.SetScale(glm::vec3(1.0f, 2.0f, 20.0f));  // Long mur vertical
    wall3.SetCollisionBox(glm::vec3(1.0f, 2.0f, 20.0f));
    obstacles.push_back(wall3);
    
    // Mur Ouest
    Game::GameObject wall4("Mur Ouest", Game::ObjectType::Obstacle);
    wall4.SetMesh(cubeMesh);
    wall4.SetPosition(glm::vec3(-10.0f, 1.0f, 0.0f));
    wall4.SetScale(glm::vec3(1.0f, 2.0f, 20.0f));
    wall4.SetCollisionBox(glm::vec3(1.0f, 2.0f, 20.0f));
    obstacles.push_back(wall4);
    
    // Obstacles au milieu (style labyrinthe)
    Game::GameObject pillar1("Pilier 1", Game::ObjectType::Obstacle);
    pillar1.SetMesh(cubeMesh);
    pillar1.SetPosition(glm::vec3(-5.0f, 1.0f, -5.0f));
    pillar1.SetScale(glm::vec3(2.0f, 2.0f, 2.0f));
    pillar1.SetCollisionBox(glm::vec3(2.0f, 2.0f, 2.0f));
    obstacles.push_back(pillar1);
    
    Game::GameObject pillar2("Pilier 2", Game::ObjectType::Obstacle);
    pillar2.SetMesh(cubeMesh);
    pillar2.SetPosition(glm::vec3(5.0f, 1.0f, 5.0f));
    pillar2.SetScale(glm::vec3(2.0f, 2.0f, 2.0f));
    pillar2.SetCollisionBox(glm::vec3(2.0f, 2.0f, 2.0f));
    obstacles.push_back(pillar2);
    
    Game::GameObject pillar3("Pilier 3", Game::ObjectType::Obstacle);
    pillar3.SetMesh(cubeMesh);
    pillar3.SetPosition(glm::vec3(0.0f, 0.5f, 0.0f));  // Au centre!
    pillar3.SetScale(glm::vec3(3.0f, 1.0f, 3.0f));
    pillar3.SetCollisionBox(glm::vec3(3.0f, 1.0f, 3.0f));
    obstacles.push_back(pillar3);
    
    // Pointer vers les obstacles pour le système de collision
    std::vector<Game::GameObject*> obstaclePtrs;
    for (auto& obs : obstacles) {
        obstaclePtrs.push_back(&obs);
    }
    // Ajouter aussi les autres obstacles comme référence pour collision
    // (mais on ne se collisionne pas avec soi-même)
    
    std::cout << "--- Création des obstacles ---\n";
    for (auto& obs : obstacles) {
        std::cout << "Créé: " << obs.GetName() << "\n";
    }
    std::cout << "Total: " << obstacles.size() << " obstacles\n\n";
    
    // 7. Créer l'ennemi
    Game::GameObject enemy("Ennemi", Game::ObjectType::Enemy);
    enemy.SetMesh(cubeMesh);
    enemy.SetPosition(glm::vec3(3.0f, 0.5f, 3.0f));  // Position de l'ennemi
    enemy.SetScale(glm::vec3(1.0f));
    enemy.SetCollisionBox(glm::vec3(1.0f));
    
    // Santé de l'ennemi
    Game::HealthSystem enemyHealth(50.0f);
    bool enemyAlive = true;
    enemyHealth.SetOnHealthChanged([&enemy](float current, float max) {
        std::cout << "[Ennemi] PV: " << current << "/" << max << "\n";
    });
    enemyHealth.SetOnDamageTaken([&enemy](float damage) {
        // Animation de dégâts
        enemy.GetAnimator().PlayHit();
    });
    enemyHealth.SetOnDeath([&enemyAlive, &enemy]() {
        std::cout << "\n*** ENNEMI VAINCU! ***\n\n";
        enemyAlive = false;
        enemy.GetAnimator().PlayDeath();
    });
    
    // Système de combat de l'ennemi
    Game::CombatSystem enemyCombat;
    enemyCombat.SetAttackDamage(10.0f);
    enemyCombat.SetAttackRange(1.5f);
    enemyCombat.SetAttackCooldown(1.0f);
    
    // 8. Créer le sol
    Game::GameObject ground("Sol", Game::ObjectType::Ground);
    ground.SetMesh(cubeMesh);
    ground.SetPosition(glm::vec3(0.0f, -0.5f, 0.0f));
    ground.SetScale(glm::vec3(30.0f, 0.1f, 30.0f));
    ground.SetCollisionEnabled(false);
    
    // 9. Créer la caméra third-person
    Engine::Camera camera(Engine::CameraType::ThirdPerson);
    camera.SetPerspective(60.0f, 800.0f / 600.0f, 0.1f, 100.0f);
    camera.SetDistance(8.0f);
    camera.SetHeight(3.0f);
    camera.SetTarget(player.GetPosition());
    
    Engine::Input::SetCursorVisible(false);
    
    // 9. Variables gameplay
    float moveSpeed = 5.0f;
    float mouseSensitivity = 0.1f;
    float zoomSpeed = 0.5f;
    bool running = true;
    float lastTime = glfwGetTime();
    
    std::cout << "\n[INFO] Boucle de jeu démarrée\n";
    std::cout << "  WASD        -> Déplacer (avec collision!)\n";
    std::cout << "  Souris      -> Tourner la caméra\n";
    std::cout << "  Molette     -> Zoomer\n";
    std::cout << "  ESPACE      -> ATTAQUER!\n";
    std::cout << "  R           -> Reset ennemi\n";
    std::cout << "  Tab         -> Curseur visible/invisible\n";
    std::cout << "  ESC         -> Quitter\n\n";
    
    while (running && !window.ShouldClose()) {
        // Delta time
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        
        // Input
        window.PollEvents();
        Engine::Input::Update();
        
        // ESC
        if (Engine::Input::IsKeyJustPressed(GLFW_KEY_ESCAPE)) {
            running = false;
        }
        
        // Tab
        if (Engine::Input::IsKeyJustPressed(GLFW_KEY_TAB)) {
            bool visible = Engine::Input::IsCursorVisible();
            Engine::Input::SetCursorVisible(!visible);
        }
        
        // ESPACE pour attaquer
        if (Engine::Input::IsKeyJustPressed(GLFW_KEY_SPACE)) {
            // Direction de l'attaque = direction du joueur
            float rotRad = glm::radians(player.GetRotationAngle());
            glm::vec3 attackDir(sin(rotRad), 0.0f, cos(rotRad));
            
            if (playerCombat.Attack(&player, player.GetPosition(), attackDir)) {
                // Animation d'attaque
                player.GetAnimator().PlayAttack();
                
                // Vérifier si on touche l'ennemi
                if (enemyAlive) {
                    Engine::AABB hitbox = playerCombat.GetCurrentHitbox();
                    if (hitbox.Intersects(enemy.GetWorldAABB())) {
                        std::cout << "*** COUP PORTÉ! ***\n";
                        enemyHealth.TakeDamage(playerCombat.GetAttackDamage());
                    }
                }
            }
        }
        
        // R pour reset ennemi
        if (Engine::Input::IsKeyJustPressed(GLFW_KEY_R)) {
            std::cout << "\n*** RESET ENNEMI ***\n";
            enemyAlive = true;
            enemyHealth.Reset();
            enemy.SetPosition(glm::vec3(3.0f, 0.5f, 3.0f));
            enemy.SetScale(glm::vec3(1.0f));
        }
        
        // Déplacement relatif à la caméra
        glm::vec3 moveDir(0.0f);
        glm::vec3 camForward = camera.GetForward();
        camForward.y = 0.0f;
        if (glm::length(camForward) > 0.001f) camForward = glm::normalize(camForward);
        
        glm::vec3 camRight = camera.GetRight();
        camRight.y = 0.0f;
        if (glm::length(camRight) > 0.001f) camRight = glm::normalize(camRight);
        
        if (Engine::Input::IsKeyPressed(GLFW_KEY_W)) moveDir += camForward;
        if (Engine::Input::IsKeyPressed(GLFW_KEY_S)) moveDir -= camForward;
        if (Engine::Input::IsKeyPressed(GLFW_KEY_A)) moveDir -= camRight;
        if (Engine::Input::IsKeyPressed(GLFW_KEY_D)) moveDir += camRight;
        
        // Appliquer mouvement avec collision
        if (glm::length(moveDir) > 0.001f) {
            moveDir = glm::normalize(moveDir);
            glm::vec3 delta = moveDir * moveSpeed * deltaTime;
            
            // Déplacer avec collision!
            bool moved = player.Move(delta, obstaclePtrs);
            
            // Rotation du joueur vers la direction
            if (moved) {
                float targetRotation = glm::degrees(atan2(moveDir.x, moveDir.z));
                player.SetRotation(targetRotation, glm::vec3(0.0f, 1.0f, 0.0f));
            }
        }
        
        // Caméra souris
        if (!Engine::Input::IsCursorVisible()) {
            glm::vec2 mouseDelta = Engine::Input::GetMouseDelta();
            camera.Rotate(mouseDelta.x * mouseSensitivity, -mouseDelta.y * mouseSensitivity);
        }
        
        // Zoom
        float scrollDelta = Engine::Input::GetMouseScrollDelta();
        if (scrollDelta != 0.0f) {
            camera.Zoom(scrollDelta * zoomSpeed);
            Engine::Input::ResetScrollDelta();
        }
        
        // Mise à jour caméra
        camera.SetTarget(player.GetPosition());
        
        // Mise à jour systèmes
        playerCombat.Update(deltaTime);
        enemyCombat.Update(deltaTime);
        playerHealth.Update(deltaTime);
        enemyHealth.Update(deltaTime);
        
        // Mise à jour animations
        player.UpdateAnimation(deltaTime);
        enemy.UpdateAnimation(deltaTime);
        
        // IA simple de l'ennemi : suivre le joueur
        if (enemyAlive) {
            glm::vec3 toPlayer = player.GetPosition() - enemy.GetPosition();
            float distToPlayer = glm::length(toPlayer);
            
            if (distToPlayer > 1.5f && distToPlayer < 10.0f) {
                // Suivre le joueur
                toPlayer = glm::normalize(toPlayer);
                glm::vec3 enemyMove = toPlayer * 2.0f * deltaTime;  // Ennemi plus lent
                enemy.Move(enemyMove, obstaclePtrs);
                
                // Tourner vers le joueur
                float enemyRot = glm::degrees(atan2(toPlayer.x, toPlayer.z));
                enemy.SetRotation(enemyRot, glm::vec3(0.0f, 1.0f, 0.0f));
            }
            
            // Attaquer si proche
            if (distToPlayer < 1.5f) {
                glm::vec3 enemyAttackDir = glm::normalize(toPlayer);
                if (enemyCombat.Attack(&enemy, enemy.GetPosition(), enemyAttackDir)) {
                    // Animation d'attaque
                    enemy.GetAnimator().PlayAttack();
                    
                    // Vérifier si on touche le joueur
                    Engine::AABB enemyHitbox = enemyCombat.GetCurrentHitbox();
                    if (enemyHitbox.Intersects(player.GetWorldAABB())) {
                        std::cout << "*** L'ENNEMI VOUS FRAPPE! ***\n";
                        playerHealth.TakeDamage(enemyCombat.GetAttackDamage());
                    }
                }
            }
        }
        
        // Rendu
        renderer.Clear(glm::vec3(0.1f, 0.12f, 0.15f));
        
        shader.Bind();
        shader.SetMat4("u_Projection", camera.GetProjectionMatrix());
        shader.SetMat4("u_View", camera.GetViewMatrix());
        
        // Dessiner le joueur
        player.Render(shader);
        
        // Dessiner l'ennemi (s'il est en vie)
        if (enemyAlive) {
            enemy.Render(shader);
        }
        
        // Dessiner les obstacles
        for (auto& obs : obstacles) {
            obs.Render(shader);
        }
        
        // Dessiner le sol
        ground.Render(shader);
        
        shader.Unbind();
        
        window.SwapBuffers();
    }
    
    Engine::Input::SetCursorVisible(true);
    std::cout << "\n[INFO] Fermeture normale\n";
    return 0;
}
