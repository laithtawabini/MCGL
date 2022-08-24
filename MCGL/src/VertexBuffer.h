#include "glad/glad.h"
#include "GLFW/glfw3.h"

class VertexBuffer
{
public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    void bind();
    void unBind();
private:
    unsigned int ID;
};