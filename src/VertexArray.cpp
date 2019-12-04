//
// Created by Emilien Lemaire on 04/12/2019.
//

#include "VertexArray.h"

VertexArray::VertexArray(GLuint t_NumberOfVAO)
    :m_NumberOfVAO(t_NumberOfVAO)
{
    m_ArrayIDs.resize(m_NumberOfVAO);
    glGenVertexArrays(m_NumberOfVAO, &m_ArrayIDs[0]);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(m_NumberOfVAO, &m_ArrayIDs[0]);
}
