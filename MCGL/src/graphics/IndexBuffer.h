#include "glad/glad.h"
#include "GLFW/glfw3.h"

class IndexBuffer
{
public:
    IndexBuffer(unsigned int* data, unsigned int size);
    ~IndexBuffer();
    void Bind();
    void UnBind();

private:
    unsigned int ID;
};