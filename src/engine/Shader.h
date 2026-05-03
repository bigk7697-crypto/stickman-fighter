#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <unordered_map>

namespace Engine {

class Shader {
public:
    Shader();
    ~Shader();

    // Créer depuis des fichiers (à implémenter plus tard)
    bool LoadFromFiles(const std::string& vertexPath, const std::string& fragmentPath);
    
    // Créer depuis des strings (pour l'instant)
    bool LoadFromSource(const std::string& vertexSource, const std::string& fragmentSource);

    void Bind() const;
    void Unbind() const;
    
    // Uniforms
    void SetInt(const std::string& name, int value);
    void SetFloat(const std::string& name, float value);
    void SetVec2(const std::string& name, const glm::vec2& value);
    void SetVec3(const std::string& name, const glm::vec3& value);
    void SetVec4(const std::string& name, const glm::vec4& value);
    void SetMat4(const std::string& name, const glm::mat4& value);

    GLuint GetProgramID() const { return m_ProgramID; }
    bool IsValid() const { return m_ProgramID != 0; }

private:
    GLuint m_ProgramID = 0;
    std::unordered_map<std::string, GLint> m_UniformCache;

    bool CompileShader(GLuint shader, const std::string& source, const std::string& type);
    GLuint CreateProgram(GLuint vertexShader, GLuint fragmentShader);
    GLint GetUniformLocation(const std::string& name);
};

} // namespace Engine
