#pragma once
#include "VertexBuffer.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray() { glDeleteVertexArrays(1, &vaoID); }
	
	void Bind() { glBindVertexArray(vaoID); }
	void Unbind() { glBindVertexArray(0); }
	uint32_t Get() { return vaoID; };
	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
private:
	unsigned int vaoID;
	
};

