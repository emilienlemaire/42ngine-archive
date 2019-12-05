//
// Created by Emilien Lemaire on 04/12/2019.
//

#include "VertexArray.h"

VertexArray::VertexArray(GLuint t_NumberOfVAO)
    :m_NumberOfVAO(t_NumberOfVAO)
{
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
    for (unsigned int & m_ArrayID : m_ArrayIDs) {
        glDeleteVertexArrays(1, &m_ArrayID);
    }
}

template<>
void VertexArray::push<GLfloat>(int index, int count, int size, bool draw) {
    glVertexAttribPointer(
            m_Locations[index],
            count,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void*)m_Offset[index]
            );
    glEnableVertexAttribArray(m_Locations[index]);
    m_Locations[index]++;
    m_Offset[index] += size;
}

void VertexArray::bind(GLuint arrayNumber) const {
    glBindVertexArray(m_ArrayIDs[arrayNumber]);
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
