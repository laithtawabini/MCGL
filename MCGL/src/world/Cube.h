#pragma once

#include <unordered_map>
#include <vector>

class Cube
{
public:
    enum class Face {
        BACK, FRONT, LEFT, RIGHT, BOTTOM, TOP
    };

    Cube();
    ~Cube();

    size_t getSizeOfData() const;
    const std::vector<float> getVertices() const;
    void removeFace(Face face);
    float* GetFaceData(Face face);

private:
    uint8_t  m_NumberOfFaces            = 6;
    uint32_t m_NumberOfFloatsInEachFace = 30;
    uint32_t m_NumberOfVertices         = 36;

private:
    std::unordered_map<Face, float*> m_CubeFacesData;
};

