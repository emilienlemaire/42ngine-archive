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
    std::vector<long> m_Offset;
    std::vector<GLuint> m_Locations;
public:
    explicit VertexArray(GLuint t_NumberOfVAO);
    ~VertexArray();

    void bind(GLuint arrayNumber) const;
    void unbind() const;

    GLuint getMNumberOfVao() const;

    template<typename T>
    void push(int index, int count, int size, bool draw = false);

    const std::vector<GLuint> &getMDrawSize() const;

    template<>
    void push<GLfloat>(int index, int count, int size, bool draw);
};



