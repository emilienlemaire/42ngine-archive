//
// Created by Emilien Lemaire on 09/12/2019.
//

#pragma once

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "ElementFeatures.h"

namespace ftn {

    struct ElementTransform {
        glm::mat4 transform = glm::mat4(1.f);
        bool enabled = false;
    };

    class Element {
    private:
        GLuint m_IndexBufferID;
        GLuint m_VertexBufferID;
        GLuint m_VertexArrayID;
        GLuint m_IndicesSize;
        GLuint m_VerticesSize;
        GLuint m_NormalsSize = 0;

        ElementTransform m_Transform;
        //ElementFeatures m_Features;

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

        /*Element(ElementFeatures t_Features,
                GLuint t_IndexBufferID,
                GLuint t_VertexBufferID,
                GLuint t_VertexArrayID,
                std::shared_ptr<IndexBuffer> t_IndexBuffer,
                std::shared_ptr<VertexBuffer> t_VertexBuffer,
                std::shared_ptr<VertexArray> t_VertexArray);*/

        void render() const;

        const ElementTransform &getTransform() const;

        void setTransform(const ElementTransform &t_Transform);

        void enableTransform(bool t_Enabled);

        glm::vec3 getColor() const { return m_Color; }

        void setColor(glm::vec3 t_Color);

        ~Element();

    };
}