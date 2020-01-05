//
// Created by Emilien Lemaire on 04/12/2019.
//

#include "VertexBuffer.h"

namespace ftn {

    VertexBuffer* VertexBuffer::s_Instance = nullptr;
    GLuint VertexBuffer::s_NumberVertexBuffers = 0;
    std::vector<GLuint> VertexBuffer::s_VertexBuffersID = std::vector<GLuint>();


    VertexBuffer::VertexBuffer() = default;

    VertexBuffer::~VertexBuffer() {
        Log::Debug("42ngine Core", "VertexBuffer destroyed");
    }

    void VertexBuffer::Create(unsigned int t_NumberOfBuffers) {
        if(!s_Instance)
            s_Instance = new VertexBuffer();

        int index = s_VertexBuffersID.size();
        s_VertexBuffersID.resize(s_VertexBuffersID.size() + t_NumberOfBuffers);

        for (int i = 0; i < t_NumberOfBuffers; ++i) {
            //Pour chaque VBO souhaité on le génère et on sauvegarde sont identifiant dans une adresse vide.
            glGenBuffers(1, &s_VertexBuffersID[index + i]);

        }

        s_NumberVertexBuffers += t_NumberOfBuffers;
    }

    void VertexBuffer::Bind(GLuint t_BufferIndex) {
        glBindBuffer(GL_ARRAY_BUFFER, s_VertexBuffersID[t_BufferIndex]);
    }

    void VertexBuffer::Unbind() {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    template<>
    void VertexBuffer::Push<GLfloat>(const std::vector<GLfloat> &t_Data) {
        //On envoie les données à la carte graphique.
        glBufferData(
                GL_ARRAY_BUFFER,
                t_Data.size() * sizeof(GLfloat),
                &t_Data[0],
                GL_STATIC_DRAW
        );
    }

    VertexBuffer *VertexBuffer::Get() {
        if(!s_Instance)
            s_Instance = new VertexBuffer();
        return s_Instance;
    }

    void VertexBuffer::Destroy() {
        if (s_Instance) {
            glDeleteBuffers(s_NumberVertexBuffers, &s_VertexBuffersID[0]);
            delete s_Instance;
            s_Instance = nullptr;
        }
    }
}