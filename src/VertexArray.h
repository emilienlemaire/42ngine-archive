//
// Created by Emilien Lemaire on 04/12/2019.
//

#pragma once


#include <GL/glew.h>
#include <vector>
#include "BufferLayout.h"

namespace ftn {
    class VertexArray {
    private:
        static VertexArray* s_Instance;
        static std::vector<BufferLayout> s_Layouts;
        static std::vector<GLuint> s_ArrayIDs;
        VertexArray();
    public:
        ~VertexArray();

        static VertexArray *Get();

        static void Bind(int t_Index);

        static void Destroy();

        static std::vector<BufferLayout> GetLayouts() { return s_Layouts; }

        static void Create(unsigned int t_Count);

        static void SetLayout(int t_Index, BufferLayout t_BufferLayout);
    };
}