//
// Created by Emilien Lemaire on 04/12/2019.
//

#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(GLuint t_NumberVertexBuffers) :
m_NumberVertexBuffers(t_NumberVertexBuffers) {
    m_VertexBuffersID.resize(m_NumberVertexBuffers);
    glGenBuffers(m_NumberVertexBuffers, &m_VertexBuffersID[0]);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(m_NumberVertexBuffers, &m_VertexBuffersID[0]);
}

void VertexBuffer::bind(GLuint vertexBufferNumber) const {
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffersID[vertexBufferNumber]);
}

void VertexBuffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::setData(GLuint size) {
    glBufferData(
            GL_ARRAY_BUFFER,
            size,
            nullptr,
            GL_STATIC_DRAW
            );
}

void VertexBuffer::addSubData(const std::vector<GLfloat>& data, long offset) const {
    glBufferSubData(
            GL_ARRAY_BUFFER,
            offset,
            data.size() * sizeof(GLfloat),
            &data[0]
            );
}
