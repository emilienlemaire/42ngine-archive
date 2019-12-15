//
// Created by Emilien Lemaire on 08/12/2019.
//

#include "IndexBuffer.h"
namespace ftn {
    IndexBuffer* IndexBuffer::s_Instance = nullptr;
    GLuint IndexBuffer::s_NumberIndexBuffers = 0;
    std::vector<GLuint> IndexBuffer::s_IndexBuffersID = std::vector<GLuint>();


    IndexBuffer::IndexBuffer() = default;

    void IndexBuffer::Create(unsigned int t_NumberOfBuffers) {
        if(!s_Instance)
            s_Instance = new IndexBuffer();

        unsigned int index = s_IndexBuffersID.size();
        s_IndexBuffersID.resize(s_IndexBuffersID.size() + t_NumberOfBuffers);

        for (int i = 0; i < t_NumberOfBuffers; ++i) {
            glGenBuffers(1, &s_IndexBuffersID[index + i]);
        }

        s_NumberIndexBuffers += t_NumberOfBuffers;
    }

    void IndexBuffer::IndexData(const std::vector<GLfloat> &t_InData, std::vector<GLuint> &t_OutIndices,
                                std::vector<GLfloat> &t_OutData) {
        std::vector<Vertex> vertices;
        std::vector<Vertex> outVertices;

        dataToVertex(t_InData, vertices);

        std::map<Vertex, int> verticesMap;

        for (auto &vertex : vertices) {
            unsigned int index;
            bool found = findVertex(verticesMap, vertex, index);
            if (found) {
                t_OutIndices.push_back(index);
            } else {
                outVertices.push_back(vertex);
                unsigned int newIndex = outVertices.size() - 1;
                t_OutIndices.push_back(newIndex);
                verticesMap[vertex] = newIndex;
            }
        }

        vertexToData(outVertices, t_OutData);
    }

    template<>
    void IndexBuffer::Push<GLuint>(std::vector<GLuint> &t_Data) {
        glBufferData(
                GL_ELEMENT_ARRAY_BUFFER,
                t_Data.size() * sizeof(GLuint),
                &t_Data[0],
                GL_STATIC_DRAW
        );
    }

    void IndexBuffer::Bind(unsigned int t_Index) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_IndexBuffersID[t_Index]);
    }

    void IndexBuffer::Unbind(unsigned int t_Index) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void IndexBuffer::dataToVertex(const std::vector<GLfloat> &t_InData, std::vector<Vertex> &t_OutVertices) {
        t_OutVertices.reserve((t_InData.size() / 7) * sizeof(Vertex));
        for (int i = 0; i < t_InData.size(); i += 7) {
            glm::vec3 position(
                    t_InData[i + 0],
                    t_InData[i + 1],
                    t_InData[i + 2]
             );
            glm::vec3 normal(
                    t_InData[i + 3],
                    t_InData[i + 4],
                    t_InData[i + 5]
             );

            float depth = t_InData[i + 6];

            t_OutVertices.push_back({
                position,
                normal,
                depth
            });
        }
    }

    bool IndexBuffer::findVertex(std::map<Vertex, int> &t_Map, Vertex &t_Vertex, unsigned int &t_Index) {
        auto it = t_Map.find(t_Vertex);
        if(it == t_Map.end()){
            return false;
        }
        t_Index = it->second;
        return true;
    }

    void IndexBuffer::vertexToData(const std::vector<Vertex>& t_Vertices, std::vector<GLfloat> &t_OutData) {
        t_OutData.clear();
        t_OutData.reserve(7 * t_Vertices.size());

        for (const auto &vertex : t_Vertices) {
            t_OutData.push_back(vertex.position.x);
            t_OutData.push_back(vertex.position.y);
            t_OutData.push_back(vertex.position.z);

            t_OutData.push_back(vertex.normals.x);
            t_OutData.push_back(vertex.normals.y);
            t_OutData.push_back(vertex.normals.z);

            t_OutData.push_back(vertex.depth);
        }
    }
}