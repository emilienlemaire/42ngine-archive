//
// Created by Emilien Lemaire on 14/12/2019.
//

#include "ElementFeatures.h"
namespace ftn {

    ElementFeatures::ElementFeatures(std::initializer_list<Feature> t_Features)
            :m_Features(t_Features)
    {
        calculateOffset();
    }

    ElementFeatures::~ElementFeatures() = default;

    void ElementFeatures::calculateOffset() {
        unsigned int offset = 0;
        for (auto &feature : m_Features) {
            feature.offset = offset;
            offset += feature.count * feature.size * sizeOfType(feature.type);
        }
    }

    unsigned int ElementFeatures::sizeOfType(FeatureType type) {
        switch (type) {
            case FeatureType::None:
                return 0;
            case FeatureType::Float:
                return sizeof(float);
            case FeatureType::Float2:
                return sizeof(float);
            case FeatureType::Float3:
                return sizeof(float);
            case FeatureType::Int:
                return sizeof(int);
        }
    }

}
