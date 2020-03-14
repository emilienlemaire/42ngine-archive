//
// Created by Emilien Lemaire on 04/12/2019.
//

#include "VertexArray.h"

namespace ftn {
    GLenum getGlType(BufferAttribType type) {
        switch (type){
            case BufferAttribType::None:
                return GL_NONE;
            case BufferAttribType::Float:
                return GL_FLOAT;
            case BufferAttribType::Float2:
                return GL_FLOAT;
            case BufferAttribType::Float3:
                return GL_FLOAT;
            case BufferAttribType::Float4:
                return GL_FLOAT;
            case BufferAttribType::Int:
                return GL_INT;
        }
    }

    VertexArray* VertexArray::s_Instance = nullptr;
    std::vector<BufferLayout> VertexArray::s_Layouts = std::vector<BufferLayout>();
    std::vector<GLuint> VertexArray::s_ArrayIDs = std::vector<GLuint>();

    VertexArray::VertexArray() = default;

    VertexArray *VertexArray::Get() {
        if(!s_Instance){
            s_Instance = new VertexArray();
        }
        return s_Instance;
    }

    void VertexArray::Create(unsigned int t_Count) {

        if(!s_Instance){
            s_Instance = new VertexArray();
        }

        int idx = s_ArrayIDs.size();
        s_ArrayIDs.resize(s_ArrayIDs.size() + t_Count);
        for (int i = 0; i < t_Count; ++i) {
            //Pour chaque VAO souhaité on le génère et on sauvegarde sont identifiant dans une adresse vide.
            glGenVertexArrays(1, &s_ArrayIDs[idx + i]);
        }
    }

    void VertexArray::Destroy() {
        for (unsigned int &s_ArrayID : s_ArrayIDs) {
            glDeleteVertexArrays(1, &s_ArrayID);
        }
        if (s_Instance) {
            delete s_Instance;
            s_Instance = nullptr;
        }
    }

    void VertexArray::Bind(int t_Index) {
        glBindVertexArray(s_ArrayIDs[t_Index]);
    }

    void VertexArray::SetLayout(int t_Index, BufferLayout t_BufferLayout) {
        //On sauvegarde la forme des données dans un tableau.
        if(t_Index >= s_Layouts.size())
            s_Layouts.push_back(t_BufferLayout);
        else
            s_Layouts[t_Index] = t_BufferLayout;

        Bind(t_Index);
        std::vector<BufferAttribute> attribs = t_BufferLayout.getAttributes();
        //On crée les attributs du VAO en fonction de la forme des données.
        for (auto &attrib : attribs) {
            glEnableVertexAttribArray(attrib.location);
            glVertexAttribPointer(
                    attrib.location,
                    attrib.count,
                    getGlType(attrib.type),
                    GL_FALSE,
                    t_BufferLayout.getStride(),
                    (void*)attrib.offset
            );
        }
    }

    VertexArray::~VertexArray() = default;

}