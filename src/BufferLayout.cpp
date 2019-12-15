//
// Created by Emilien Lemaire on 15/12/2019.
//

#include "BufferLayout.h"

namespace ftn {

    BufferLayout::BufferLayout(std::initializer_list<BufferAttribute> t_Attributes)
        :m_Attributes(t_Attributes), m_Stride(0)
    {
        calculateOffsetsAndStride();
    }

    void BufferLayout::calculateOffsetsAndStride() {
        unsigned int offset = 0;
        unsigned int stride = 0;
        unsigned int location = 0;
        for (auto &attribute : m_Attributes) {
            attribute.offset = offset;
            attribute.location = location;
            offset += attribute.size;
            stride += attribute.size;
            location++;
        }

        m_Stride = stride;
    }

    BufferLayout::~BufferLayout() = default;
}