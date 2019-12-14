//
// Created by Emilien Lemaire on 08/12/2019.
//

#include "IndexBuffer.h"
namespace ftn {
    IndexBuffer::IndexBuffer(GLuint t_NumberOfBuffers)
            : m_NumberOfBuffers(t_NumberOfBuffers) {
        m_IndexBufferIDs.resize(t_NumberOfBuffers);
        glGenBuffers(m_NumberOfBuffers, &m_IndexBufferIDs[0]);
        Log::Debug("IndexBuffer constructed");
    }

    IndexBuffer::~IndexBuffer() {
        glDeleteBuffers(m_NumberOfBuffers, &m_IndexBufferIDs[0]);
        Log::Debug("IndexBuffer destructed");
    }

    void IndexBuffer::indexData(std::vector<GLfloat> &t_InData,
                                std::vector<GLuint> &t_OutIndices,
                                std::vector<GLfloat> &t_OutData)  {
        t_OutIndices.clear();
        std::vector<Vertex> inData;
        std::vector<Vertex> outData;
        dataToVertex(t_InData, inData);
        std::map<Vertex, GLuint> vertices;

        for (auto vertex : inData) {
            GLuint index;
            bool found = findVertex(vertices, vertex, index);
            if (found) {
                t_OutIndices.push_back(index);
            } else {
                outData.push_back(vertex);
                GLuint newIndex = (GLuint) outData.size() - 1;
                t_OutIndices.push_back(newIndex);
                vertices[vertex] = newIndex;
            }
        }

        vertexToData(outData, t_OutData);
    }

    void IndexBuffer::setData(GLuint t_Size) {
        glBufferData(
                GL_ELEMENT_ARRAY_BUFFER,
                t_Size,
                nullptr,
                GL_STATIC_DRAW
        );
    }

    void IndexBuffer::addSubData(const std::vector<GLuint> &t_Data, long t_Offset) const {
        glBufferSubData(
                GL_ELEMENT_ARRAY_BUFFER,
                t_Offset,
                t_Data.size() * sizeof(GLuint),
                &t_Data[0]
        );
    }

    void IndexBuffer::bind(GLuint t_BufferNumber) const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferIDs[t_BufferNumber]);
    }

    void IndexBuffer::unbind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void IndexBuffer::dataToVertex(const std::vector<GLfloat> &t_InData, std::vector<Vertex> &t_OutData) {

        t_OutData.reserve((t_InData.size() / 7) * sizeof(Vertex));
        for (unsigned long i = 0; i < t_InData.size(); i += 7) {
            t_OutData.push_back(Vertex{
                    glm::vec3(
                            t_InData[i + 0],
                            t_InData[i + 1],
                            t_InData[i + 2]
                    ),
                    glm::vec3(
                            t_InData[i + 3],
                            t_InData[i + 4],
                            t_InData[i + 5]
                    ),
                    t_InData[i + 6]
            });
        }
    }

    bool IndexBuffer::findVertex(std::map<Vertex, GLuint> &t_Map, Vertex &t_Vertex, GLuint &t_Index) {
        auto it = t_Map.find(t_Vertex);
        if (it == t_Map.end()) {
            return false;
        } else {
            Vertex vert = it->first;
            t_Index = it->second;
            return true;
        }
    }

    void IndexBuffer::vertexToData(std::vector<Vertex> &t_Vertices, std::vector<GLfloat> &t_OutData) {
        t_OutData.clear();
        t_OutData.reserve(t_Vertices.size() * 3);
        for (auto vertex : t_Vertices) {
            t_OutData.push_back(vertex.position.x);
            t_OutData.push_back(vertex.position.y);
            t_OutData.push_back(vertex.position.z);
        }
    }

    void IndexBuffer::vertexToData(std::vector<Vertex> &t_Vertices, std::vector<GLfloat> &t_OutData,
                                   std::vector<GLfloat> &t_OutNormals) {
        t_OutData.clear();
        t_OutData.reserve(t_Vertices.size() * 3);
        t_OutNormals.clear();
        t_OutNormals.reserve(t_Vertices.size() * 3);
        for (auto vertex : t_Vertices) {
            t_OutData.push_back(vertex.position.x);
            t_OutData.push_back(vertex.position.y);
            t_OutData.push_back(vertex.position.z);
            t_OutNormals.push_back(vertex.normals.x);
            t_OutNormals.push_back(vertex.normals.y);
            t_OutNormals.push_back(vertex.normals.z);
        }

    }
}