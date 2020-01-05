//
// Created by Emilien Lemaire on 08/12/2019.
//

#include "IndexBuffer.h"
namespace ftn {
    IndexBuffer* IndexBuffer::s_Instance = nullptr;
    GLuint IndexBuffer::s_NumberIndexBuffers = 0;
    std::vector<GLuint> IndexBuffer::s_IndexBuffersID = std::vector<GLuint>();


    IndexBuffer::IndexBuffer() = default;

    void IndexBuffer::Create(unsigned int t_NumberOfBuffers) {
        if(!s_Instance)
            s_Instance = new IndexBuffer();

        unsigned int index = s_IndexBuffersID.size();
        s_IndexBuffersID.resize(s_IndexBuffersID.size() + t_NumberOfBuffers);

        for (int i = 0; i < t_NumberOfBuffers; ++i) {
            //Pour chaque IBO souhaité on le génère et on sauvegarde sont identifiant dans une adresse vide.
            glGenBuffers(1, &s_IndexBuffersID[index + i]);
        }

        s_NumberIndexBuffers += t_NumberOfBuffers;
    }

    void IndexBuffer::IndexData(const std::vector<GLfloat> &t_InData, std::vector<GLuint> &t_OutIndices,
                                std::vector<GLfloat> &t_OutData) {
        std::vector<Vertex> vertices;
        std::vector<Vertex> outVertices;

        //On transforme les données en un tableau de Vertex pour la map.
        dataToVertex(t_InData, vertices);

        std::map<Vertex, int> verticesMap;

        for (auto &vertex : vertices) {
            unsigned int index;
            bool found = findVertex(verticesMap, vertex, index);
            if (found) {
                //Si le point est trouvé (i.e. toutes ses données sont similaires) on l'ajoute au tableau d'indice.
                t_OutIndices.push_back(index);
            } else {
                //Si le point n'est pas trouvé on ajoute ce point au tableau de vertices et on lui associe un nouvel indice.
                outVertices.push_back(vertex);
                unsigned int newIndex = outVertices.size() - 1;
                t_OutIndices.push_back(newIndex);
                verticesMap[vertex] = newIndex;
            }
        }

        //On transforme les Vertex en données lisible par la carte graphique.
        vertexToData(outVertices, t_OutData);
    }

    template<>
    void IndexBuffer::Push<GLuint>(std::vector<GLuint> &t_Data) {
        //On envoie les données à la carte graphique.
        glBufferData(
                GL_ELEMENT_ARRAY_BUFFER,
                t_Data.size() * sizeof(GLuint), //La carte graphique à besion de la taille en byte, pas juste du nombre de données
                &t_Data[0],
                GL_STATIC_DRAW
        );
    }

    void IndexBuffer::Bind(unsigned int t_Index) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_IndexBuffersID[t_Index]);
    }

    void IndexBuffer::Unbind(unsigned int t_Index) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void IndexBuffer::dataToVertex(const std::vector<GLfloat> &t_InData, std::vector<Vertex> &t_OutVertices) {
        //On réserve la mémoire pour éviter les changements d'addresse inutiles.
        t_OutVertices.reserve((t_InData.size() / 9) * sizeof(Vertex));
        for (int i = 0; i < t_InData.size(); i += 9) {
            glm::vec3 position(
                    t_InData[i + 0],
                    t_InData[i + 1],
                    t_InData[i + 2]
             );
            glm::vec3 normal(
                    t_InData[i + 3],
                    t_InData[i + 4],
                    t_InData[i + 5]
             );

            float depth = t_InData[i + 6];

            glm::vec2 texture(
                    t_InData[i + 7],
                    t_InData[i + 8]
                    );

            t_OutVertices.push_back({
                position,
                normal,
                depth,
                texture
            });
        }
    }

    bool IndexBuffer::findVertex(std::map<Vertex, int> &t_Map, Vertex &t_Vertex, unsigned int &t_Index) {
        auto it = t_Map.find(t_Vertex);
        if(it == t_Map.end()){
            return false;
        }
        t_Index = it->second;
        return true;
    }

    void IndexBuffer::vertexToData(const std::vector<Vertex>& t_Vertices, std::vector<GLfloat> &t_OutData) {
        //On s'assure qu'il n'y a pas de données parasites et
        // on réserve la mémoire pour éviter les changements d'addresse inutiles.
        t_OutData.clear();
        t_OutData.reserve(9 * t_Vertices.size());

        for (const auto &vertex : t_Vertices) {
            t_OutData.push_back(vertex.position.x);
            t_OutData.push_back(vertex.position.y);
            t_OutData.push_back(vertex.position.z);

            t_OutData.push_back(vertex.normals.x);
            t_OutData.push_back(vertex.normals.y);
            t_OutData.push_back(vertex.normals.z);

            t_OutData.push_back(vertex.depth);

            t_OutData.push_back(vertex.texture.s);
            t_OutData.push_back(vertex.texture.t);
        }
    }

    void IndexBuffer::Destroy() {
        if(s_Instance){
            glDeleteBuffers(s_NumberIndexBuffers, &s_IndexBuffersID[0]);
            delete s_Instance;
            s_Instance = nullptr;
        }
    }

    IndexBuffer::~IndexBuffer() {
        Log::Debug("42ngine Core", "IndexBuffer destroyed");
    }
}