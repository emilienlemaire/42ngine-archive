//
// Created by Emilien Lemaire on 04/12/2019.
//

#pragma once

class VertexBuffer {
private:
    GLuint m_NumberVertexBuffers;
    std::vector<GLuint> m_VertexBuffersID;
public:
    explicit VertexBuffer(GLuint t_NumberVertexBuffers);
    ~VertexBuffer();

    void bind(GLuint vertexBufferNumber) const;
    void unbind() const;
    static void setData(GLuint size);
    void addSubData(const std::vector<GLfloat>& data, long offset = 0) const;
};



