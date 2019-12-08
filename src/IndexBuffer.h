//
// Created by Emilien Lemaire on 08/12/2019.
//

#pragma once

#include <map>

struct Vertex{
    glm::vec3 position;
    bool operator<(const Vertex vertex) const{
            return glm::length(this->position) < glm::length(vertex.position);
    }
};

class IndexBuffer {
private:
    GLuint m_NumberOfBuffers;
    std::vector<GLuint> m_IndexBufferIDs;
public:
    explicit IndexBuffer(GLuint t_NumberOfBuffers);
    ~IndexBuffer();

    void indexData(std::vector<GLfloat> &t_InData,
            std::vector<GLubyte> &t_OutIndices,
            std::vector<GLfloat> &t_OutData) const;
    void setData(GLuint size);
    void addSubData(const std::vector<GLubyte>& data, long offset = 0) const;
    void bind(GLuint t_BufferNumber) const;
    void unbind() const;

private:
    void dataToVertex(std::vector<GLfloat>& t_Data, std::vector<Vertex>& t_Result) const;
    void vertexToData(std::vector<Vertex>& t_Vertices, std::vector<GLfloat>& t_OutData) const;
    bool findVertex(std::map<Vertex, GLubyte>& map, Vertex& vertex, GLubyte& index) const;
};



