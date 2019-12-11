//
// Created by Emilien Lemaire on 09/12/2019.
//

#pragma once

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

namespace ftn {
    class Element {
    private:
        GLuint m_IndexBufferID;
        GLuint m_VertexBufferID;
        GLuint m_VertexArrayID;
        GLuint m_IndicesSize;
        GLuint m_VerticesSize;
        GLuint m_NormalsSize = 0;

        std::shared_ptr<VertexArray> m_VertexArray;
        std::shared_ptr<IndexBuffer> m_IndexBuffer;
        std::shared_ptr<VertexBuffer> m_VertexBuffer;
        glm::vec3 m_Color = glm::vec3(1.0, 1.0, 1.0);
    public:
        Element(std::vector<GLfloat>& t_Data,
                GLuint t_IndexBufferID,
                GLuint t_VertexBufferID,
                GLuint t_VertexArrayID,
                std::shared_ptr<IndexBuffer> t_IndexBuffer,
                std::shared_ptr<VertexBuffer> t_VertexBuffer,
                std::shared_ptr<VertexArray> t_VertexArray);

        Element(std::vector<GLfloat>& t_Data,
                std::vector<GLfloat>& t_Normals,
                GLuint t_IndexBufferID,
                GLuint t_VertexBufferID,
                GLuint t_VertexArrayID,
                std::shared_ptr<IndexBuffer> t_IndexBuffer,
                std::shared_ptr<VertexBuffer> t_VertexBuffer,
                std::shared_ptr<VertexArray> t_VertexArray);

        void render() const;

        glm::vec3 getColor() const { return m_Color; }

        void setColor(glm::vec3 t_Color);

        ~Element();
    };
}