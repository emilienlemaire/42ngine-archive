#include <utility>

//
// Created by Emilien Lemaire on 15/12/2019.
//

#pragma once

#include <CppLogger/src/Log.h>

namespace ftn {
    //Chaque attribut de donnée doit avoir un type prédéfini
    enum class BufferAttribType{
        None = 0, Float, Float2, Float3, Float4, Int
    };

    //On récupère la taille des données en octet en fonction du type.
    static unsigned int sizeFromType(BufferAttribType type){
        switch (type){

            case BufferAttribType::None:
                Log::Error("42ngine Core", "Unknown buffer attribute type");
                return 0;
            case BufferAttribType::Float:
                return 4;
            case BufferAttribType::Float2:
                return 2 * 4;
            case BufferAttribType::Float3:
                return 3 * 4;
            case BufferAttribType::Float4:
                return 4 * 4;
            case BufferAttribType::Int:
                return 4;
        }
    }

    //On récupère le nombre d'élément dans chaque donnée en fonction du type.
    static unsigned int countFromType(BufferAttribType type){
        switch (type){

            case BufferAttribType::None:
                Log::Error("42ngine Core", "Unknown buffer attribute type");
                return 0;
            case BufferAttribType::Float:
                return 1;
            case BufferAttribType::Float2:
                return 2;
            case BufferAttribType::Float3:
                return 3;
            case BufferAttribType::Float4:
                return 4;
            case BufferAttribType::Int:
                return 1;
        }
    }


    struct BufferAttribute {
        std::string name;
        BufferAttribType type;
        unsigned int size;
        unsigned int count;
        unsigned long offset;
        unsigned int location;

        BufferAttribute(std::string name, BufferAttribType type)
            :name(std::move(name)),
            type(type),
            size(sizeFromType(type)),
            count(countFromType(type)),
            offset(0),
            location(0)
        {}
    };
    class BufferLayout {
    private:
        std::vector<BufferAttribute> m_Attributes;

        unsigned int m_Stride;

    public:
        BufferLayout(std::initializer_list<BufferAttribute> t_Attributes);

        ~BufferLayout();

        inline unsigned int getStride() { return m_Stride; }

        inline std::vector<BufferAttribute> getAttributes() { return m_Attributes; }

    private:
        void calculateOffsetsAndStride();
    };

}
