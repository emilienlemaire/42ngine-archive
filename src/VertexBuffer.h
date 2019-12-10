//
// Created by Emilien Lemaire on 04/12/2019.
//

#pragma once

#include <GL/glew.h>

namespace ftn {
    class VertexBuffer {
    private:
        GLuint m_NumberVertexBuffers;
        std::vector<GLuint> m_VertexBuffersID;
    public:
        explicit VertexBuffer(GLuint t_NumberVertexBuffers);

        ~VertexBuffer();

        void bind(GLuint t_BufferIndex) const;

        void unbind() const;

        static void setData(GLuint t_Size);

        void addSubData(const std::vector<GLfloat> &t_Data, long t_Offset = 0) const;
    };
}