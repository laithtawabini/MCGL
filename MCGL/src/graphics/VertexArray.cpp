#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &vaoID);
	this->Bind();
}
#include <iostream>
void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	this->Bind();
	vb.Bind();

	uint32_t offset = 0;
	uint32_t index = 0;

	for (const auto& element : layout.GetElements())
	{
		glEnableVertexAttribArray(index);

		if (element.valuesType == TYPE::BYTE)
		{
			glVertexAttribPointer(
				index,
				element.countOfValues,
				GL_BYTE,
				element.isNormalized,
				layout.GetStride(),
				(void*)offset
			);
		}
		else
		{
			glVertexAttribPointer(
				index,
				element.countOfValues,
				GL_FLOAT,
				element.isNormalized,
				layout.GetStride(),
				(void*) offset
			);
		}

		if (element.valuesType == TYPE::BYTE)
			offset += element.countOfValues * sizeof(char);
		else 
			offset += element.countOfValues * sizeof(float);

		index++;
	}
}