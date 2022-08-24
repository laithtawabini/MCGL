#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &ID);
}

void VertexBuffer::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VertexBuffer::unBind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

