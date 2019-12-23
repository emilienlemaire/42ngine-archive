//
// Created by Emilien Lemaire on 15/12/2019.
//

#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>

namespace ftn {
    class Texture {
    private:
        static Texture* s_Instance;

        static std::vector<GLuint> s_TextureIDs;

        Texture();
    public:

        static void Create(unsigned int t_NumberOfTextures);

        static void Bind(unsigned int t_Index);

        static void Push(unsigned int t_Index, const char* t_TexturePath);

        ~Texture();
    };
}
