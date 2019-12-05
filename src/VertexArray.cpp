//
// Created by Emilien Lemaire on 04/12/2019.
//

#include "VertexArray.h"

VertexArray::VertexArray(GLuint t_NumberOfVAO)
    :m_NumberOfVAO(t_NumberOfVAO)
{
    m_ArrayIDs.resize(m_NumberOfVAO);
    m_DrawSize.resize(m_NumberOfVAO);
    glGenVertexArrays(m_NumberOfVAO, &m_ArrayIDs[0]);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(m_NumberOfVAO, &m_ArrayIDs[0]);
}

template<>
void VertexArray::Push<GLfloat>(int count, int size, int arrayID, bool draw) {
    glVertexAttribPointer(
            m_Location,
            count,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void*)m_Offset
            );
    m_Location++;
    m_Offset += size;
    if (draw){
        m_DrawSize[arrayID] += size / sizeof(GLfloat);
    }
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
