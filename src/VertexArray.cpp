//
// Created by Emilien Lemaire on 04/12/2019.
//

#include "VertexArray.h"

namespace ftn {
    VertexArray::VertexArray(GLuint t_NumberOfVAO)
            : m_NumberOfVAO(t_NumberOfVAO) {
        m_ArrayIDs.resize(m_NumberOfVAO);
        m_DrawSize.resize(m_NumberOfVAO);
        m_Locations.resize(m_NumberOfVAO);
        m_Offset.resize(m_NumberOfVAO);

        for (unsigned int i = 0; i < m_NumberOfVAO; i++) {
            m_Locations[i] = 0;
            m_Offset[i] = 0;
            glGenVertexArrays(1, &m_ArrayIDs[i]);
        }
    }

    VertexArray::~VertexArray() {
        for (unsigned int &m_ArrayID : m_ArrayIDs) {
            glDeleteVertexArrays(1, &m_ArrayID);
        }
    }

    template<>
    void VertexArray::push<GLfloat>(int t_Index, int t_Count, int t_Size) {
        glVertexAttribPointer(
                m_Locations[t_Index],
                t_Count,
                GL_FLOAT,
                GL_FALSE,
                0,
                (void *) m_Offset[t_Index]
        );
        glEnableVertexAttribArray(m_Locations[t_Index]);
        m_Locations[t_Index]++;
        m_Offset[t_Index] += t_Size;
    }

    void VertexArray::bind(GLuint t_ArrayIndex) const {
        glBindVertexArray(m_ArrayIDs[t_ArrayIndex]);
    }

    void VertexArray::unbind() const {
        glBindVertexArray(0);
    }

    GLuint VertexArray::getMNumberOfVao() const {
        return m_NumberOfVAO;
    }

    const std::vector<GLuint> &VertexArray::getMDrawSize() const {
        return m_DrawSize;
    }
}