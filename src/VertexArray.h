//
// Created by Emilien Lemaire on 04/12/2019.
//

#pragma once


#include <vector>

class VertexArray {
private:
    GLuint m_NumberOfVAO;
    std::vector<GLuint> m_ArrayIDs;
    std::vector<GLuint> m_DrawSize;
    long m_Offset = 0;
    GLuint m_Location = 0;
public:
    explicit VertexArray(GLuint t_NumberOfVAO);
    ~VertexArray();

    void bind(GLuint arrayNumber) const;
    void unbind() const;

    GLuint getMNumberOfVao() const;

    template<typename T>
    void Push(int count, int size, int arrayID = 0, bool draw = false);

    const std::vector<GLuint> &getMDrawSize() const;

    template<>
    void Push<GLfloat>(int count, int size, int arrayID, bool draw);
};



