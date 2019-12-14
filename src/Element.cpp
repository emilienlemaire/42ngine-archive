//
// Created by Emilien Lemaire on 09/12/2019.
//

#include "Element.h"

#include <utility>

namespace ftn {

    Element::Element(std::vector<GLfloat> &t_Data, GLuint t_IndexBufferID, GLuint t_VertexBufferID, GLuint t_VertexArrayID,
                     std::shared_ptr<IndexBuffer> t_IndexBuffer, std::shared_ptr<VertexBuffer> t_VertexBuffer, std::shared_ptr<VertexArray> t_VertexArray)
                     :m_IndexBufferID(t_IndexBufferID),
                     m_VertexBufferID(t_VertexBufferID),
                     m_VertexArrayID(t_VertexArrayID),
                     m_IndexBuffer(std::move(t_IndexBuffer)),
                     m_VertexBuffer(std::move(t_VertexBuffer)),
                     m_VertexArray(std::move(t_VertexArray))
    {

        m_VertexArray->bind(m_VertexArrayID);
        m_VertexBuffer->bind(m_VertexBufferID);
        m_IndexBuffer->bind(m_IndexBufferID);

        std::vector<GLuint> indices;
        std::vector<GLfloat> vertices;
        IndexBuffer::indexData(t_Data, indices, vertices);
        m_IndicesSize = indices.size();
        m_VerticesSize = vertices.size();

        m_VertexArray->push<GLfloat>(m_VertexArrayID, 3, m_VerticesSize * sizeof(GLfloat));
        m_VertexBuffer->setData(m_VerticesSize * sizeof(GLfloat));
        m_VertexBuffer->addSubData(vertices);
        m_IndexBuffer->setData(m_IndicesSize * sizeof(GLuint));
        m_IndexBuffer->addSubData(indices);
    }

    Element::Element(std::vector<GLfloat> &t_Data, std::vector<GLfloat> &t_Normals, GLuint t_IndexBufferID, GLuint t_VertexBufferID, GLuint t_VertexArrayID,
                     std::shared_ptr<IndexBuffer> t_IndexBuffer, std::shared_ptr<VertexBuffer> t_VertexBuffer, std::shared_ptr<VertexArray> t_VertexArray)
                     :m_IndexBufferID(t_IndexBufferID),
                     m_VertexBufferID(t_VertexBufferID),
                     m_VertexArrayID(t_VertexArrayID),
                     m_IndexBuffer(std::move(t_IndexBuffer)),
                     m_VertexBuffer(std::move(t_VertexBuffer)),
                     m_VertexArray(std::move(t_VertexArray))
    {

        m_VertexArray->bind(m_VertexArrayID);
        m_VertexBuffer->bind(m_VertexBufferID);
        m_IndexBuffer->bind(m_IndexBufferID);

        std::vector<GLuint> indices;
        std::vector<GLfloat> vertices;
        std::vector<GLfloat> normals;
        IndexBuffer::indexData(t_Data, t_Normals, indices, vertices, normals);
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
        glDrawElements(GL_TRIANGLES, m_IndicesSize, GL_UNSIGNED_INT, nullptr);
    }

    Element::~Element() = default;

    void Element::setColor(glm::vec3 t_Color) {
        m_Color = t_Color;
    }

    const ElementTransform &Element::getTransform() const {
        return m_Transform;
    }

    void Element::setTransform(const ElementTransform &t_Transform) {
        m_Transform = t_Transform;
    }

    void Element::enableTransform(bool t_Enabled){
        m_Transform.enabled = t_Enabled;
    }
}