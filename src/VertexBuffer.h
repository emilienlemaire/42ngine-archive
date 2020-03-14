//
// Created by Emilien Lemaire on 04/12/2019.
//

#pragma once

#include <GL/glew.h>
#include <CppLogger/src/Log.h>

namespace ftn {
    class VertexBuffer {
    private:
        static VertexBuffer* s_Instance;

        static GLuint s_NumberVertexBuffers;

        static std::vector<GLuint> s_VertexBuffersID;

        VertexBuffer();
    public:

        ~VertexBuffer();

        static void Create(unsigned int t_NumberOfBuffers);
        static void Destroy();

        VertexBuffer* Get();

        static void Bind(GLuint t_BufferIndex);

        static void Unbind();

        template <class T>
                static void Push(const std::vector<T>& t_Data);
                template<>  void Push<GLfloat>(const std::vector<GLfloat>& t_Data);
    };
}