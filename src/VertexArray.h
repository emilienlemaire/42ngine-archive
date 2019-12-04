//
// Created by Emilien Lemaire on 04/12/2019.
//

#pragma once


#include <vector>

class VertexArray {
private:
    GLuint m_NumberOfVAO;
    std::vector<GLuint> m_ArrayIDs;
public:
    explicit VertexArray(GLuint t_NumberOfVAO);
    ~VertexArray();
};



