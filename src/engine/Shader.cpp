#include "Shader.h"
#include <iostream>
#include <sstream>

namespace Engine {

Shader::Shader() = default;

Shader::~Shader() {
    if (m_ProgramID != 0) {
        glDeleteProgram(m_ProgramID);
    }
}

bool Shader::LoadFromSource(const std::string& vertexSource, const std::string& fragmentSource) {
    // Créer les shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Compiler vertex shader
    if (!CompileShader(vertexShader, vertexSource, "Vertex")) {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return false;
    }

    // Compiler fragment shader
    if (!CompileShader(fragmentShader, fragmentSource, "Fragment")) {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return false;
    }

    // Créer le programme
    m_ProgramID = CreateProgram(vertexShader, fragmentShader);

    // Nettoyer les shaders individuels
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return m_ProgramID != 0;
}

bool Shader::CompileShader(GLuint shader, const std::string& source, const std::string& type) {
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    // Vérifier les erreurs
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "[ERREUR] Compilation " << type << " Shader:\n" << infoLog << "\n";
        return false;
    }

    std::cout << "[OK] " << type << " Shader compilé\n";
    return true;
}

GLuint Shader::CreateProgram(GLuint vertexShader, GLuint fragmentShader) {
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    // Vérifier le linkage
    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cerr << "[ERREUR] Linkage Program:\n" << infoLog << "\n";
        glDeleteProgram(program);
        return 0;
    }

    std::cout << "[OK] Shader Program lié (ID: " << program << ")\n";
    return program;
}

void Shader::Bind() const {
    glUseProgram(m_ProgramID);
}

void Shader::Unbind() const {
    glUseProgram(0);
}

GLint Shader::GetUniformLocation(const std::string& name) {
    // Cache pour éviter les recherches répétées
    auto it = m_UniformCache.find(name);
    if (it != m_UniformCache.end()) {
        return it->second;
    }

    GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
    if (location == -1) {
        std::cerr << "[AVERTISSEMENT] Uniform '" << name << "' non trouvé\n";
    }
    
    m_UniformCache[name] = location;
    return location;
}

void Shader::SetInt(const std::string& name, int value) {
    glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetFloat(const std::string& name, float value) {
    glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetVec2(const std::string& name, const glm::vec2& value) {
    glUniform2f(GetUniformLocation(name), value.x, value.y);
}

void Shader::SetVec3(const std::string& name, const glm::vec3& value) {
    glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
}

void Shader::SetVec4(const std::string& name, const glm::vec4& value) {
    glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);
}

void Shader::SetMat4(const std::string& name, const glm::mat4& value) {
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &value[0][0]);
}

bool Shader::LoadFromFiles(const std::string& vertexPath, const std::string& fragmentPath) {
    // À implémenter plus tard avec chargement de fichiers
    std::cerr << "[ERREUR] LoadFromFiles pas encore implémenté\n";
    return false;
}

} // namespace Engine
