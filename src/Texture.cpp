//
// Created by Emilien Lemaire on 15/12/2019.
//

#include "Texture.h"

namespace ftn {
    Texture* Texture::s_Instance = nullptr;
    std::vector<GLuint> Texture::s_TextureIDs = std::vector<GLuint>();

    Texture::Texture() = default;


    void Texture::Create(unsigned int t_NumberOfTextures) {
        if(!s_Instance) {
            s_Instance = new Texture();
        }
        s_TextureIDs.reserve(s_TextureIDs.size() + t_NumberOfTextures);
        for (int i = 0; i < t_NumberOfTextures; ++i) {
            GLuint tID;
            glGenTextures(1, &tID);
            s_TextureIDs.push_back(tID);
        }
    }

    void Texture::Push(unsigned int t_Index, const char *t_TexturePath) {
        Bind(t_Index);

        cv::Mat image = cv::imread(t_TexturePath, CV_LOAD_IMAGE_UNCHANGED);
        cv::flip(image, image, 0);


        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RGBA,
                image.cols,
                image.rows,
                0,
                GL_BGRA,
                GL_UNSIGNED_BYTE,
                image.ptr()
        );

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }

    void Texture::Bind(unsigned int t_Index) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, s_TextureIDs[t_Index]);
    }

    void Texture::Destroy() {
        if(s_Instance){
            delete s_Instance;
        }
        Log::Debug("Texture destroyed");
    }

    Texture::~Texture(){
        for (auto &textureId : s_TextureIDs) {
            glDeleteTextures(1, &textureId);
        }
    };
}

