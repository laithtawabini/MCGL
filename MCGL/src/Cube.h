
//specify an initial position
//specify the size of the cube
#include <memory>
class Cube
{
public:
    Cube()
    {
        // vertices = (float*)alloca(SIZE * sizeof(float));
        float data[] = { 
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
        };

        for(int i = 0; i < 5 * 36; i++)
            vertices[i] = data[i];
        
    }

    size_t getSizeOfData() const { return sizeof(vertices); };
    const float* getVertices() const { return vertices; }
    
private:
    float vertices[5 * 36];
};



class Arrow
{
public:
    Arrow()
    {
        // vertices = (float*)alloca(SIZE * sizeof(float));
        float data[] = {
            0.0f, 0.5f, 0.0f,
            0.5f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.5f,

            0.0f, 0.5f, 0.0f,
            -0.5f, 0.0f, 0.0f,
            0.5f, 0.0f, 0.0f,

            0.0f, 0.5f, 0.0f,
            0.0f, 0.0f, -0.5f,
            -0.5f, 0.0f, 0.0f,

            0.0f, 0.5f, 0.0f,
            0.0f, 0.0f, -0.5f,
            0.5f, 0.0f, 0.0f,

            0.0f, -2.0f, 0.0f,
        };

        for (int i = 0; i < 3 * 13; i++)
            vertices[i] = data[i];

    }

    size_t getSizeOfData() const { return sizeof(vertices); };
    const float* getVertices() const { return vertices; }

private:
    float vertices[3 * 13];
};

//#------------------Arrow Data buffers-------------------#// 
//unsigned int arrVAO;
//glGenVertexArrays(1, &arrVAO);
//
//// VertexBuffer VBO(vertices, sizeof(vertices));
//VertexBuffer arrVBO(arrow.getVertices(), arrow.getSizeOfData());
//IndexBuffer arrIBO(indices, sizeof(indices));
//
//glBindVertexArray(arrVAO);
//
//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//glEnableVertexAttribArray(0);
//
///*glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//glEnableVertexAttribArray(2);*/
//
//// glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//// glEnableVertexAttribArray(2);