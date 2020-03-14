//
// Created by Emilien Lemaire on 04/12/2019.
//

#include "Shader.h"
#include <Log.h>
namespace ftn {
    Shader::Shader(const std::string &t_VertexShaderPath, const std::string &t_FragmentShaderPath) {
        GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

        // Read the Vertex Shader code from the file
        std::string VertexShaderCode;
        std::ifstream VertexShaderStream(t_VertexShaderPath, std::ios::in);
        if (VertexShaderStream.is_open()) {
            std::stringstream sstr;
            sstr << VertexShaderStream.rdbuf();
            VertexShaderCode = sstr.str();
            VertexShaderStream.close();
        } else {
            printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n",
                   t_VertexShaderPath.c_str());
            getchar();
            exit(EXIT_FAILURE);
        }

        // Read the Fragment Shader code from the file
        std::string FragmentShaderCode;
        std::ifstream FragmentShaderStream(t_FragmentShaderPath, std::ios::in);
        if (FragmentShaderStream.is_open()) {
            std::stringstream stringStream;
            stringStream << FragmentShaderStream.rdbuf();
            FragmentShaderCode = stringStream.str();
            FragmentShaderStream.close();
        }

        GLint Result = GL_FALSE;
        int InfoLogLength;


        // Compile Vertex Shader
        printf("Compiling shader : %s\n", t_VertexShaderPath.c_str());
        char const *VertexSourcePointer = VertexShaderCode.c_str();
        glShaderSource(VertexShaderID, 1, &VertexSourcePointer, nullptr);
        glCompileShader(VertexShaderID);

        // Check Vertex Shader
        glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if (InfoLogLength > 0) {
            std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
            glGetShaderInfoLog(VertexShaderID, InfoLogLength, nullptr, &VertexShaderErrorMessage[0]);
            printf("%s\n", &VertexShaderErrorMessage[0]);
        }



        // Compile Fragment Shader
        printf("Compiling shader : %s\n", t_FragmentShaderPath.c_str());
        char const *FragmentSourcePointer = FragmentShaderCode.c_str();
        glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, nullptr);
        glCompileShader(FragmentShaderID);

        // Check Fragment Shader
        glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if (InfoLogLength > 0) {
            std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
            glGetShaderInfoLog(FragmentShaderID, InfoLogLength, nullptr, &FragmentShaderErrorMessage[0]);
            printf("%s\n", &FragmentShaderErrorMessage[0]);
        }



        // Link the program
        printf("Linking program\n");
        m_ProgramID = glCreateProgram();
        glAttachShader(m_ProgramID, VertexShaderID);
        glAttachShader(m_ProgramID, FragmentShaderID);
        glLinkProgram(m_ProgramID);
        glValidateProgram(m_ProgramID);

        // Check the program
        glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &Result);
        glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if (InfoLogLength > 0) {
            std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
            glGetProgramInfoLog(m_ProgramID, InfoLogLength, nullptr, &ProgramErrorMessage[0]);
            printf("%s\n", &ProgramErrorMessage[0]);
        }

        glDetachShader(m_ProgramID, VertexShaderID);
        glDetachShader(m_ProgramID, FragmentShaderID);

        glDeleteShader(VertexShaderID);
        glDeleteShader(FragmentShaderID);
    }

    Shader::~Shader() {
        glDeleteProgram(m_ProgramID);
    }

    void Shader::bind() const {
        glUseProgram(m_ProgramID);
    }

    void Shader::unbind() const {
        glUseProgram(0);
    }

    //Les fonctions ci-dessous envoie les uniforms au programme des shaders
    void Shader::addUniformMat4(const GLchar *t_Name, glm::mat4 t_Mat) {
        GLint matrixID = getLocation(t_Name);
        glUniformMatrix4fv(matrixID, 1, GL_FALSE, &t_Mat[0][0]);
    }

    void Shader::addUniform1f(const GLchar *t_Name, float t_Value) {
        GLint uniformID = getLocation(t_Name);
        glUniform1f(uniformID, t_Value);
    }

    void Shader::addUniform3f(const GLchar *t_Name, glm::vec3 t_Vec) {
        GLint uniformID = getLocation(t_Name);
        glUniform3f(uniformID, t_Vec[0], t_Vec[1], t_Vec[2]);
    }


    void Shader::addUniform4f(const GLchar *t_Name, glm::vec4 t_Vec) {
        GLint uniformID = getLocation(t_Name);
        glUniform4f(uniformID, t_Vec[0], t_Vec[1], t_Vec[2], t_Vec[3]);
    }

    void Shader::addUniform1i(const GLchar *t_Name, int t_Value) {
        GLint uniformID = getLocation(t_Name);
        glUniform1i(uniformID, t_Value);
    }

    //On sauvegarde l'emplacement des uniforms afin d'éviter de le demander à la carte graphique à chaque changement de l'uniform.
    int Shader::getLocation(const char *t_Name) {
        auto it = m_UniformsIDs.find(t_Name);
        if (it == m_UniformsIDs.end()){
            int location = glGetUniformLocation(m_ProgramID, t_Name);
            if (location == -1)
                Log::Warn("42ngine Core", "Uniform " + std::string(t_Name) + " not found");

            m_UniformsIDs[t_Name] = location;
            return location;
        }
        return it->second;
    }
}
