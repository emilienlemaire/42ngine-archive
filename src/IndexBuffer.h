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
        glm::vec2 texture = glm::vec2(0.f);

        bool operator<(const Vertex vertex) const {
            return memcmp((void*)this, (void*)&vertex, sizeof(Vertex)) > 0;
        }
    };

    class IndexBuffer {
    private:
        static IndexBuffer* s_Instance;

        static GLuint s_NumberIndexBuffers;

        static std::vector<GLuint> s_IndexBuffersID;

        IndexBuffer();
    public:
        static void Create(unsigned int t_NumberOfBuffers);

        static void IndexData(const std::vector<GLfloat>& t_InData,
                std::vector<GLuint>& t_OutIndices,
                std::vector<GLfloat>& t_OutData);

        static void Bind(unsigned int t_Index);

        static void Unbind(unsigned int t_Index);

        template<class T>
                static void Push(std::vector<T>& t_Data);
                template<> void Push<GLuint>(std::vector<GLuint >& t_Data);

    private:
        static void dataToVertex(const std::vector<GLfloat> &t_InData, std::vector<Vertex> &t_OutVertices);

        static bool findVertex(std::map<Vertex, int> &t_Map, Vertex &t_Vertex, unsigned int &t_Index);

        static void vertexToData(const std::vector<Vertex>& t_Vertices, std::vector<GLfloat> &t_OutData);
    };
}


