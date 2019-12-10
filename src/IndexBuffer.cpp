//
// Created by Emilien Lemaire on 08/12/2019.
//

#include "IndexBuffer.h"
namespace ftn {
    IndexBuffer::IndexBuffer(GLuint t_NumberOfBuffers)
            : m_NumberOfBuffers(t_NumberOfBuffers) {
        m_IndexBufferIDs.resize(t_NumberOfBuffers);
        for (GLuint i = 0; i < t_NumberOfBuffers; ++i) {
            glGenBuffers(1, &m_IndexBufferIDs[i]);
        }
    }

    IndexBuffer::~IndexBuffer() {
        for (GLuint i = 0; i < m_NumberOfBuffers; ++i) {
            glDeleteBuffers(1, &m_IndexBufferIDs[i]);
        }
    }

    void IndexBuffer::indexData(std::vector<GLfloat> &t_InData,
                                std::vector<GLuint> &t_OutIndices,
                                std::vector<GLfloat> &t_OutData) const {
        t_OutIndices.clear();
        std::vector<Vertex> inData;
        std::vector<Vertex> outData;
        dataToVertex(t_InData, inData);
        std::map<Vertex, GLuint> vertices;

        for (unsigned long i = 0; i < inData.size(); ++i) {
            GLuint index;
            Vertex vertex = inData[i];
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

    void IndexBuffer::dataToVertex(const std::vector<GLfloat> &t_InData, std::vector<Vertex> &t_OutData) const {

        t_OutData.reserve((t_InData.size() / 3) * sizeof(Vertex));
        for (unsigned long i = 0; i < t_InData.size(); i += 3) {
            t_OutData.push_back(Vertex{
                    glm::vec3(
                            t_InData[i + 0],
                            t_InData[i + 1],
                            t_InData[i + 2]
                    )
            });
        }
    }

    bool IndexBuffer::findVertex(std::map<Vertex, GLuint> &t_Map, Vertex &t_Vertex, GLuint &t_Index) const {
        auto it = t_Map.find(t_Vertex);
        if (it == t_Map.end()) {
            return false;
        } else {
            Vertex vert = it->first;
            if(vert.position.x == t_Vertex.position.x
            && vert.position.y == t_Vertex.position.y
            && vert.position.z == t_Vertex.position.z)
            {
                t_Index = it->second;
                return true;
            }
            return false;
        }
    }

    void IndexBuffer::vertexToData(std::vector<Vertex> &t_Vertices, std::vector<GLfloat> &t_OutData) const {
        t_OutData.clear();
        t_OutData.reserve(t_Vertices.size() * 3);
        for (auto vertex : t_Vertices) {
            t_OutData.push_back(vertex.position.x);
            t_OutData.push_back(vertex.position.y);
            t_OutData.push_back(vertex.position.z);
        }
    }

    void IndexBuffer::indexData(std::vector<GLfloat> &t_InData, std::vector<GLfloat> &t_InNormals,
                                std::vector<GLuint> &t_OutIndices, std::vector<GLfloat> &t_OutData,
                                std::vector<GLfloat> &t_OutNormals) const {
        t_OutIndices.clear();
        std::vector<Vertex> inData;
        std::vector<Vertex> outData;
        dataToVertex(t_InData, t_InNormals, inData);
        std::map<Vertex, GLuint> vertices;

        for (unsigned long i = 0; i < inData.size(); ++i) {
            GLuint index;
            Vertex vertex = inData[i];
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

        vertexToData(outData, t_OutData, t_OutNormals);

    }

    void IndexBuffer::dataToVertex(const std::vector<GLfloat> &t_InData, const std::vector<GLfloat> &t_Normals,
                                   std::vector<Vertex> &t_OutData) const {t_OutData.reserve((t_InData.size() / 3) * sizeof(Vertex));
        for (unsigned long i = 0; i < t_InData.size(); i += 3) {
            t_OutData.push_back(Vertex{
                    glm::vec3(
                            t_InData[i + 0],
                            t_InData[i + 1],
                            t_InData[i + 2]
                    ),
                    glm::vec3(
                            t_Normals[i + 0],
                            t_Normals[i + 1],
                            t_Normals[i + 2]
                    )
            });
        }

    }

    void IndexBuffer::vertexToData(std::vector<Vertex> &t_Vertices, std::vector<GLfloat> &t_OutData,
                                   std::vector<GLfloat> &t_OutNormals) const {
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