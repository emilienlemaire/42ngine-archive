//
// Created by Emilien Lemaire on 09/12/2019.
//

#include "Element.h"

namespace ftn {

    Element::Element(std::vector<GLfloat> &t_Data, GLuint t_IndexBufferID, GLuint t_VertexBufferID, GLuint t_VertexArrayID,
                     IndexBuffer* t_IndexBuffer, VertexBuffer* t_VertexBuffer, VertexArray* t_VertexArray)
                     :m_IndexBufferID(t_IndexBufferID),
                     m_VertexBufferID(t_VertexBufferID),
                     m_VertexArrayID(t_VertexArrayID),
                     m_IndexBuffer(t_IndexBuffer),
                     m_VertexBuffer(t_VertexBuffer),
                     m_VertexArray(t_VertexArray)
    {

        m_VertexArray->bind(m_VertexArrayID);
        m_VertexBuffer->bind(m_VertexBufferID);
        m_IndexBuffer->bind(m_IndexBufferID);

        std::vector<GLuint> indices;
        std::vector<GLfloat> vertices;
        m_IndexBuffer->indexData(t_Data, indices, vertices);
        m_IndicesSize = indices.size();
        m_VerticesSize = vertices.size();

        m_VertexArray->push<GLfloat>(m_VertexArrayID, 3, m_VerticesSize * sizeof(GLfloat));
        m_VertexBuffer->setData(m_VerticesSize * sizeof(GLfloat));
        m_VertexBuffer->addSubData(vertices);
        m_IndexBuffer->setData(m_IndicesSize * sizeof(GLuint));
        m_IndexBuffer->addSubData(indices);
    }

    Element::Element(std::vector<GLfloat> &t_Data, std::vector<GLfloat> &t_Normals, GLuint t_IndexBufferID, GLuint t_VertexBufferID, GLuint t_VertexArrayID,
                     IndexBuffer* t_IndexBuffer, VertexBuffer* t_VertexBuffer, VertexArray* t_VertexArray)
                     :m_IndexBufferID(t_IndexBufferID),
                     m_VertexBufferID(t_VertexBufferID),
                     m_VertexArrayID(t_VertexArrayID),
                     m_IndexBuffer(t_IndexBuffer),
                     m_VertexBuffer(t_VertexBuffer),
                     m_VertexArray(t_VertexArray)
    {

        m_VertexArray->bind(m_VertexArrayID);
        m_VertexBuffer->bind(m_VertexBufferID);
        m_IndexBuffer->bind(m_IndexBufferID);

        std::vector<GLuint> indices;
        std::vector<GLfloat> vertices;
        std::vector<GLfloat> normals;
        m_IndexBuffer->indexData(t_Data, t_Normals, indices, vertices, normals);
        m_IndicesSize = indices.size();
        m_VerticesSize = vertices.size();
        m_NormalsSize = normals.size();

        m_VertexArray->push<GLfloat>(m_VertexArrayID, 3, m_VerticesSize * sizeof(GLfloat));
        m_VertexArray->push<GLfloat>(m_VertexArrayID, 3, m_NormalsSize * sizeof(GLfloat));
        m_VertexBuffer->setData(m_VerticesSize * sizeof(GLfloat) + m_NormalsSize * sizeof(GLfloat) );
        m_VertexBuffer->addSubData(vertices);
        m_VertexBuffer->addSubData(normals, m_VerticesSize * sizeof(GLfloat));
        m_IndexBuffer->setData(m_IndicesSize * sizeof(GLuint));
        m_IndexBuffer->addSubData(indices);
    }

    void Element::render() const {
        m_VertexArray->bind(m_VertexArrayID);
        m_IndexBuffer->bind(m_IndexBufferID);
        glDrawElements(GL_TRIANGLES, m_IndicesSize, GL_UNSIGNED_INT, nullptr);
    }

    Element::~Element() {

    }

    void Element::setColor(glm::vec3 t_Color) {
        m_Color = t_Color;
    }
}