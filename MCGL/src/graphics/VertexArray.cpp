#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &vaoID);
	this->Bind();
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	this->Bind();
	vb.Bind();

	uint32_t offset = 0;
	uint32_t index = 0;

	for (const auto& element : layout.GetElements())
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(
			index,
			element.countOfValues,
			element.valuesType,
			element.isNormalized,
			layout.GetStride(),
			(void*) offset
		);

		offset += element.countOfValues * sizeof(element.valuesType);
		index++;
	}
}