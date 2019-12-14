//
// Created by Emilien Lemaire on 14/12/2019.
//
#pragma once
#include <utility>

namespace ftn{
    enum class FeatureType {
        None = 0, Float, Float2, Float3, Int
    };

    static unsigned int sizeFromType(FeatureType type){
        switch (type){
            case FeatureType::None:
                Log::Error("Unknown feature type");
                return 0;
            case FeatureType::Float:
                return 1;
            case FeatureType::Float2:
                return 2;
            case FeatureType::Float3:
                return 3;
            case FeatureType::Int:
                return 1;
        }
    }

    struct Feature {
        std::string name;
        FeatureType type;
        unsigned int count; //Number of elements (for a triangle == 3 vertex)
        unsigned int size; //Size of one feature (example vertex == 3 floats)
        unsigned int offset;
        Feature(std::string  name, FeatureType type, unsigned int count)
            :name(std::move(name)), type(type), count(count), size(sizeFromType(type)), offset(0)
        {}
    };

    class ElementFeatures {
    private:
        std::vector<Feature> m_Features;

    public:
        ElementFeatures(std::initializer_list<Feature> t_Features);

        ~ElementFeatures();

    private:
        void calculateOffset();
        unsigned int sizeOfType(FeatureType type);
    };

}



