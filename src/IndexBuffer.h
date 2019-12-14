//
// Created by Emilien Lemaire on 08/12/2019.
//

#pragma once

#include <map>
#include <GL/glew.h>

namespace ftn {

    struct Vertex {
        glm::vec3 position;
        glm::vec3 normals = glm::vec3(0.f);
        float depth = 0.f;

        bool operator<(const Vertex vertex) const {
            return memcmp((void*)this, (void*)&vertex, sizeof(Vertex)) > 0;
        }
    };

    class IndexBuffer {
    private:
        GLuint m_NumberOfBuffers;

        std::vector<GLuint> m_IndexBufferIDs;

    public:
        explicit IndexBuffer(GLuint t_NumberOfBuffers);

        ~IndexBuffer();

        static void indexData(std::vector<GLfloat> &t_InData,
                       std::vector<GLuint> &t_OutIndices,
                       std::vector<GLfloat> &t_OutData);

        static void indexData(std::vector<GLfloat> &t_InData,
                       std::vector<GLfloat> &t_InNormals,
                       std::vector<GLuint> &t_OutIndices,
                       std::vector<GLfloat> &t_OutData,
                       std::vector<GLfloat> &t_OutNormals);

        static void indexData(std::vector<GLfloat> &t_InData,
                       std::vector<GLfloat> &t_InNormals,
                       std::vector<GLubyte> &t_InDepth,
                       std::vector<GLuint> &t_OutIndices,
                       std::vector<GLfloat> &t_OutData,
                       std::vector<GLfloat> &t_OutNormals,
                       std::vector<GLubyte> &t_OutDepth);

        void setData(GLuint t_Size);

        void addSubData(const std::vector<GLuint> &t_Data, long t_Offset = 0) const;

        void bind(GLuint t_BufferNumber) const;

        void unbind() const;

    private:
        static void dataToVertex(const std::vector<GLfloat> &t_InData, std::vector<Vertex> &t_OutData);

        static void dataToVertex(const std::vector<GLfloat> &t_InData, const std::vector<GLfloat> &t_Normals, std::vector<Vertex> &t_OutData);

        static void vertexToData(std::vector<Vertex> &t_Vertices, std::vector<GLfloat> &t_OutData);

        static void vertexToData(std::vector<Vertex> &t_Vertices, std::vector<GLfloat> &t_OutData, std::vector<GLfloat> &t_OutNormals);

        static bool findVertex(std::map<Vertex, GLuint> &t_Map, Vertex &t_Vertex, GLuint &t_Index);
    };
}


