#include "Cube.h"


Cube::Cube()
{
    m_CubeFacesData[Face::BACK] = new float[] {
        -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,     1.0f / 3.0f, 0.0f,
        0.5f, 0.5f, -0.5f,      1.0f / 3.0f, 1.0f,        //back face        
        0.5f, 0.5f, -0.5f,      1.0f / 3.0f, 1.0f,
        -0.5f, 0.5f, -0.5f,     0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,    0.0f, 0.0f
    };

    m_CubeFacesData[Face::FRONT] = new float[] {
        -0.5f, -0.5f, 0.5f,     0.0f, 0.0f,
        0.5f, -0.5f, 0.5f,      1.0f / 3.0f, 0.0f,
        0.5f, 0.5f, 0.5f,       1.0f / 3.0f, 1.0f,        //front face
        0.5f, 0.5f, 0.5f,       1.0f / 3.0f, 1.0f,
        -0.5f, 0.5f, 0.5f,      0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f,     0.0f, 0.0f
    };

    m_CubeFacesData[Face::LEFT] = new float[] {
        -0.5f, 0.5f, 0.5f,      1.0f / 3.0f, 1.0f,
        -0.5f, 0.5f, -0.5f,     0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,              //left face
        -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,
        -0.5f, -0.5f, 0.5f,     1.0f / 3.0f, 0.0f,
        -0.5f, 0.5f, 0.5f,      1.0f / 3.0f, 1.0f
    };

    m_CubeFacesData[Face::RIGHT] = new float[] {
        0.5f, 0.5f, 0.5f,       1.0f / 3.0f, 1.0f,
        0.5f, 0.5f, -0.5f,      0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,     0.0f, 0.0f,        //right face
        0.5f, -0.5f, -0.5f,     0.0f, 0.0f,
        0.5f, -0.5f, 0.5f,      1.0f / 3.0f, 0.0f,
        0.5f, 0.5f, 0.5f,       1.0f / 3.0f, 1.0f
    };
        
    m_CubeFacesData[Face::BOTTOM] = new float[] { 
        -0.5f, -0.5f, -0.5f,    1.0f / 3.0f, 0.0f, 
        0.5f, -0.5f, -0.5f,     2.0f / 3.0f, 0.0f,
        0.5f, -0.5f, 0.5f,      2.0f / 3.0f, 1.0f,  //bottom face
        0.5f, -0.5f, 0.5f,      2.0f / 3.0f, 1.0f,
        -0.5f, -0.5f, 0.5f,     1.0f / 3.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,    1.0f / 3.0f, 0.0f
    };
    

    m_CubeFacesData[Face::TOP] = new float[] {
        -0.5f, 0.5f, -0.5f,     2.0f / 3.0f, 0.f,
        0.5f, 0.5f, -0.5f,      1.0f, 0.0f,
        0.5f, 0.5f, 0.5f,       1.0f, 1.0f,        //top face
        0.5f, 0.5f, 0.5f,       1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f,      2.0f / 3.0f, 1.0f,
        -0.5f, 0.5f, -0.5f,     2.0f / 3.0f, 0.f,
    };
}

Cube::~Cube()
{
    for (auto& map : m_CubeFacesData)
    {
        delete[] map.second;
    }
}

size_t Cube::getSizeOfData() const { return sizeof(float) * m_NumberOfFaces * m_NumberOfFloatsInEachFace; }

const std::vector<float> Cube::getVertices() const
{
    std::vector<float> retV;

    for (auto& face : m_CubeFacesData)
    {
        for (int i = 0; i < m_NumberOfFloatsInEachFace; i++)
        {
            retV.push_back(face.second[i]);
        }
    }

    return retV;
}

void Cube::removeFace(Face face)
{
    delete[] m_CubeFacesData[face];
    m_CubeFacesData.erase(face);
    m_NumberOfFaces--;
    m_NumberOfVertices -= 6;
}

float* Cube::GetFaceData(Face face)
{
    switch (face)
    {
        case Face::BACK:   return m_CubeFacesData[Face::BACK];
        case Face::FRONT:  return m_CubeFacesData[Face::FRONT];
        case Face::LEFT:   return m_CubeFacesData[Face::LEFT];
        case Face::RIGHT:  return m_CubeFacesData[Face::RIGHT];
        case Face::BOTTOM: return m_CubeFacesData[Face::BOTTOM];
        case Face::TOP:    return m_CubeFacesData[Face::TOP];
    }
}

