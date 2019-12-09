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
namespace ftn {
    class Shader {
    private:
        GLuint m_ProgramID;
    public:
        Shader(const std::string &t_VertexShaderPath, const std::string &t_FragmentShaderPath);

        ~Shader();

        void bind() const;

        void unbind() const;

        void addUniform4f(const GLchar *t_Name, glm::vec4 t_Vec) const;

        void addUniform3f(const GLchar *t_Name, glm::vec3 t_Vec) const;

        void addUniformMat4(const GLchar *t_Name, glm::mat4 t_Mat) const;

        inline GLuint getProgramId() const { return m_ProgramID; };
    };
}