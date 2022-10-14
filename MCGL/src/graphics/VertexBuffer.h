#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "VertexBufferLayout.h"

class VertexBuffer
{
public:
    VertexBufferLayout layout;

    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    void Bind() const;
    void UnBind() const;

    void UpdateData(const void* data, unsigned int size);
private:
    unsigned int ID;
};