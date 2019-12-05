//
// Created by Emilien Lemaire on 04/12/2019.
//

#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

class Shader {
private:
    GLuint m_ProgramID;
public:
    Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    ~Shader();
    void bind() const;
    void unbind() const;
    void addUniform4f(const GLchar *name, glm::vec4 vec) const;
    void addUniform3f(const GLchar* name, glm::vec3 vec) const;
    void addUniformMat4(const GLchar *name, glm::mat4 mat) const;
    inline GLuint getProgramId() const { return m_ProgramID; };
};




