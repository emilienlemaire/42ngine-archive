//
// Created by Emilien Lemaire on 04/12/2019.
//

#pragma once


#include <GL/glew.h>
#include <vector>

namespace ftn {
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

        void bind(GLuint t_ArrayIndex) const;

        void unbind() const;

        GLuint getMNumberOfVao() const;

        template<typename T>
        void push(int t_Index, int t_Count, int t_Size);

        const std::vector<GLuint> &getMDrawSize() const;

        template<>
        void push<GLfloat>(int t_Index, int t_Count, int t_Size);
    };
}