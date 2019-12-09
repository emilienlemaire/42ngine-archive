//
// Created by Emilien Lemaire on 08/12/2019.
//

#include "IndexBuffer.h"
namespace ftn {
    IndexBuffer::IndexBuffer(GLuint t_NumberOfBuffers)
            : m_NumberOfBuffers(t_NumberOfBuffers) {
        m_IndexBufferIDs.reserve(t_NumberOfBuffers);
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
                                std::vector<GLubyte> &t_OutIndices,
                                std::vector<GLfloat> &t_OutData) const {
        t_OutIndices.clear();
        std::vector<Vertex> inData;
        std::vector<Vertex> outData;
        dataToVertex(t_InData, inData);
        std::map<Vertex, GLubyte> vertices;

        for (unsigned long i = 0; i < inData.size(); ++i) {
            GLubyte index;
            Vertex vertex = inData[i];
            bool found = findVertex(vertices, vertex, index);
            if (found) {
                t_OutIndices.push_back(index);
            } else {
                outData.push_back(vertex);
                GLubyte newIndex = (GLubyte) outData.size() - 1;
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

    void IndexBuffer::addSubData(const std::vector<GLubyte> &t_Data, long t_Offset) const {
        glBufferSubData(
                GL_ELEMENT_ARRAY_BUFFER,
                t_Offset,
                t_Data.size() * sizeof(GLubyte),
                &t_Data[0]
        );
    }

    void IndexBuffer::bind(GLuint t_BufferNumber) const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferIDs[t_BufferNumber]);
    }

    void IndexBuffer::unbind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void IndexBuffer::dataToVertex(std::vector<GLfloat> &t_Data, std::vector<Vertex> &t_Result) const {
        for (unsigned long i = 0; i < t_Data.size(); i += 3) {
            t_Result.push_back(Vertex{
                    glm::vec3(
                            t_Data[i + 0],
                            t_Data[i + 1],
                            t_Data[i + 2]
                    )
            });
        }
    }

    bool IndexBuffer::findVertex(std::map<Vertex, GLubyte> &t_Map, Vertex &t_Vertex, GLubyte &t_Index) const {
        auto it = t_Map.find(t_Vertex);
        if (it == t_Map.end()) {
            return false;
        } else {
            t_Index = it->second;
            return true;
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
}