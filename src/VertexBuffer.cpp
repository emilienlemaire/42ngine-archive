//
// Created by Emilien Lemaire on 04/12/2019.
//

#include "VertexBuffer.h"

namespace ftn {
    VertexBuffer::VertexBuffer(GLuint t_NumberVertexBuffers) :
            m_NumberVertexBuffers(t_NumberVertexBuffers) {
        m_VertexBuffersID.resize(m_NumberVertexBuffers);
        glGenBuffers(m_NumberVertexBuffers, &m_VertexBuffersID[0]);
    }

    VertexBuffer::~VertexBuffer() {
        glDeleteBuffers(m_NumberVertexBuffers, &m_VertexBuffersID[0]);
    }

    void VertexBuffer::bind(GLuint t_BufferIndex) const {
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffersID[t_BufferIndex]);
    }

    void VertexBuffer::unbind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void VertexBuffer::setData(GLuint t_Size) {
        glBufferData(
                GL_ARRAY_BUFFER,
                t_Size,
                nullptr,
                GL_STATIC_DRAW
        );
    }

    void VertexBuffer::addSubData(const std::vector<GLfloat> &t_Data, long t_Offset) const {
        glBufferSubData(
                GL_ARRAY_BUFFER,
                t_Offset,
                t_Data.size() * sizeof(GLfloat),
                &t_Data[0]
        );
    }
}