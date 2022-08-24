#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(unsigned int* data, unsigned int size)
{
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &ID);
}

void IndexBuffer::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void IndexBuffer::unBind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

